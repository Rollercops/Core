//
//  Socket.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "Socket.h"

SocketError::SocketError(std::string message)
    : Error("SocketError"), _message(message) {}

std::string SocketError::toString() {
    return (getType() + ": " + _message);
}

Socket::Socket() : RCObject("Socket") {
    _descriptor = socket(AF_INET , SOCK_STREAM , 0);

    if (_descriptor == -1) {
        throw SocketError("socket function return -1");
    }
}

Socket::Socket(int descriptor, std::string address, int port)
: RCObject("Socket") {
    _descriptor = descriptor;
    _address = address;
    _port = port;
}

Socket::~Socket() {}

Socket* Socket::connect(std::string address, Number<int> port) {
    Socket* socket = new Socket();
    socket->_address = address;
    socket->_port = port.getNumber();

    struct sockaddr_in server;

    bzero(&server, sizeof(server));
    server.sin_addr.s_addr = inet_addr(socket->_address.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(socket->_port);

    int ret_connect = ::connect(socket->_descriptor,
                                (struct sockaddr *)&server ,
                                sizeof(server));
    if (ret_connect == -1) {
        throw SocketError("connect function return something < 0");
    }
    bzero(&server, sizeof(server));
    socket->_open = true;
    socket->_ptr = socket;
    return (socket);
}

Socket* Socket::fromServerSocket(int fd, std::string address, int port) {
    Socket* socket = new Socket(fd, address, port);
    socket->_ptr = socket;
    socket->_open = true;
    return (socket);
}


int Socket::write(std::string message) {
    ssize_t nbCharSend;
    if (_open) {
        nbCharSend = send(_descriptor, message.c_str(), message.length(), 0);
        if (nbCharSend == -1) {
            _sendOnError(SocketError("send function return -1"));
            return (-1);
        }
        else if (nbCharSend == strlen(message.c_str())) {
            return (1);
        }
    }
    return (0);
}

void Socket::_sendOnError(SocketError error) {
    if (_onError != NULL) {
        _onError(*this, error);
    } else {
        Logger::root->log(Level::WARNING, error.toString());
    }
}

void Socket::_sendOnDone() {
    close();
    if (_onDone != NULL) {
        _onDone(*this);
    } else {
        Logger::root->log(Level::INFO, "server close the connexion");
    }
    destroy();
}

int Socket::_read() {
    size_t MAXMSG = 512;
    char buf[MAXMSG];
    ssize_t nbytes;

    bzero(buf, MAXMSG);
    nbytes = recv(_descriptor, &buf, MAXMSG, 0);
    if (nbytes == -1) {
        _sendOnError(SocketError("read error"));
    } else if (nbytes == 0) {
        _sendOnDone();
    } else if (_onReceive != NULL) {
        _onReceive(*this, std::string(buf));
    } else {
        throw SocketError("onReceive is null");
    }
    return (1);
}

void Socket::listen(void (*onReceive)(Socket socket,
                                      std::string message),
                    void (*onDone)(Socket socket),
                    void (*onError)(Socket socket,
                                    SocketError error)) {
    _onReceive = onReceive;
    _onError = onError;
    _onDone = onDone;
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    int ret_thread;
    ret_thread = pthread_create(&_thread, NULL,  threadRead, this);
    if (ret_thread < 0) {
        _sendOnError(SocketError("pthread failed, try without thread"));
        threadRead(this);
    }
#else
    threadRead(this);
#endif
}

void Socket::wait() {
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_join(_thread, NULL);
#endif
}

void Socket::destroy() {
    _onReceive = NULL;
    _onDone = NULL;
    _onError = NULL;
    delete _ptr;
}

void Socket::close() {
    _open = false;
    ::close(_descriptor);
}

bool Socket::isOpen() const {
    return (_open);
}

int Socket::getFd() const {
    return (_descriptor);
}

void* Socket::threadRead(void* data) {
    Socket* socket = reinterpret_cast<Socket*>(data);
    fd_set read_fd_set, active_fd_set;
    FD_ZERO(&read_fd_set);
    FD_SET(socket->_descriptor, &read_fd_set);
    try {
        while (socket->_open) {
            active_fd_set = read_fd_set;
            if (select(FD_SETSIZE, &active_fd_set, NULL, NULL, NULL) == -1) {
                socket->_sendOnError(SocketError("select error"));
            }
            else if (FD_ISSET(socket->getFd(), &active_fd_set)) {
                if (socket->_read() == -1) {
                    socket->_sendOnError(SocketError("read error"));
                } else {
                    FD_CLR(0, &active_fd_set);
                }
            }
        }
    }
    catch (SocketError error) {
        socket->_sendOnError(error);
    }
    return (NULL);
}

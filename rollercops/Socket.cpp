//
//  Socket.cpp
//  logging
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

Socket::~Socket() {}

Socket& Socket::connect(std::string address, Number<int> port, bool v6Only) {
    Socket* socket = new Socket();
    socket->_address = address;
    socket->_port = port.getNumber();
    socket->_v6Only = v6Only;

    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(socket->_address.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(socket->_port);

    int ret_connect = ::connect(socket->_descriptor,
                                (struct sockaddr *)&server ,
                                sizeof(server));
    if (ret_connect == -1) {
        throw SocketError("connect function return something < 0");
    }
    socket->_open = true;
    socket->_ptr = socket;
    return (*socket);
}

bool Socket::write(std::string message) const {
    ssize_t nbCharSend;
    nbCharSend = send(_descriptor, message.c_str(), message.length(), 0);
    if (nbCharSend == -1) {
        sendOnError(SocketError("send function return -1"));
    }
    if (nbCharSend == strlen(message.c_str())) {
        return (true);
    }
    return (false);
}

void Socket::sendOnError(SocketError error) const {
    if (_onError != NULL) {
        _onError(*this, error);
    } else {
        Logger::root->log(Level::SEVERE, error.toString());
    }
}

void Socket::sendOnClose() {
    if (_onDone != NULL) {
        close();
        _onDone(*this);
    } else {
        close();
        Logger::root->log(Level::INFO, "server close the connexion");
    }
}

int Socket::read() {
    size_t MAXMSG = 512;
    char buf[MAXMSG];
    ssize_t nbytes;

    bzero(buf, MAXMSG);
    nbytes = recv(_descriptor, &buf, MAXMSG, 0);
    if (nbytes == -1) {
        sendOnError(SocketError("read error"));
    } else if (nbytes == 0) {
        sendOnClose();
    } else if (_onReceive != NULL) {
        _onReceive(*this, std::string(buf));
    } else {
        throw SocketError("onReceive is null");
    }
    return (1);
}

void Socket::listen(void (*onReceive)(const Socket& socket
                                      , std::string message),
                    void (*onDone)(const Socket& socket),
                    void (*onError)(const Socket& socket
                                    , SocketError error)) {
    _onReceive = onReceive;
    _onError = onError;
    _onDone = onDone;
    int ret_thread;
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
    ret_thread = pthread_create(&_thread, NULL,  threadRead, this);
    if (ret_thread < 0) {
        sendOnError(SocketError("pthread failed, try without thread"));
        threadRead(this);
    }
# else
    threadRead(this);
# endif
}

void Socket::wait() {
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_join(_thread, NULL);
# endif
}

void Socket::destroy() {
    delete _ptr;
}

void Socket::close() {
    _onReceive = NULL;
    _onError = NULL;
    _open = false;
    ::close(_descriptor);
}

bool Socket::isOpen() const {
    return (_open);
}

int Socket::getFd() const {
    return (_descriptor);
}

void *threadRead(void* data) {
    Socket* socket = reinterpret_cast<Socket*>(data);
    fd_set read_fd_set, active_fd_set;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd_set);
    FD_SET(socket->getFd(), &read_fd_set);
    try {
        while (socket->isOpen()) {
            active_fd_set = read_fd_set;
            if (select(FD_SETSIZE, &active_fd_set, NULL, NULL, NULL) == -1) {
                throw SocketError("select error");
            }
            if (FD_ISSET(socket->getFd(), &active_fd_set)) {
                if (socket->read() == -1) {
                    socket->sendOnError(SocketError("read error"));
                } else {
                    FD_CLR(0, &active_fd_set);
                }
            }
        }
    }
    catch (SocketError error) {
        socket->sendOnError(error);
    }
    return (NULL);
}
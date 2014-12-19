//
//  Socket.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "TcpSocket.h"

TcpSocketError::TcpSocketError(std::string message)
    : Error("TcpSocketError"), _message(message) {}

std::string TcpSocketError::toString() {
    return (getType() + ": " + _message);
}

TcpSocket::TcpSocket() : RCObject("TcpSocket") {
    _descriptor = socket(AF_INET , SOCK_STREAM , 0);

    if (_descriptor == -1) {
        throw TcpSocketError("socket function return -1");
    }
}

TcpSocket::TcpSocket(int descriptor, std::string address, int port)
: RCObject("TcpSocket") {
    _descriptor = descriptor;
    _address = address;
    _port = port;
}

TcpSocket::~TcpSocket() {}

TcpSocket* TcpSocket::connect(std::string address, Number<int> port) {
    TcpSocket* socket = new TcpSocket();
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
        throw TcpSocketError("connect function return something < 0");
    }
    bzero(&server, sizeof(server));
    socket->_open = true;
    socket->_ptr = socket;
    return (socket);
}

TcpSocket* TcpSocket::fromServerSocket(int fd,
                                       std::string address,
                                       int port,
                                       ServerSocket* ss) {
    TcpSocket* socket = new TcpSocket(fd, address, port);
    socket->_ptr = socket;
    socket->_open = true;
    socket->_parent = ss;
    return (socket);
}


int TcpSocket::write(std::string message) {
    ssize_t nbCharSend;
    if (_open) {
        nbCharSend = send(_descriptor, message.c_str(), message.length(), 0);
        if (nbCharSend == -1) {
            _sendOnError(TcpSocketError("send function return -1"));
            return (-1);
        } else if (nbCharSend == strlen(message.c_str())) {
            return (1);
        }
    }
    return (0);
}

void TcpSocket::_sendOnError(TcpSocketError error) {
    if (_onError != NULL) {
        _onError(*this, error);
    } else {
        Logger::root->log(Level::WARNING, error.toString());
    }
}

void TcpSocket::_sendOnDone() {
    close();
    if (_onDone != NULL) {
        _onDone(*this);
    } else {
        Logger::root->log(Level::INFO, "server close the connexion");
    }
    if (_parent != NULL) {
        _parent->clientLeave(this);
    }
    destroy();
}

int TcpSocket::_read() {
    size_t MAXMSG = 512;
    char buf[MAXMSG];
    ssize_t nbytes;

    bzero(buf, MAXMSG);
    nbytes = recv(_descriptor, &buf, MAXMSG, 0);
    if (nbytes == -1) {
        _sendOnError(TcpSocketError("read error"));
    } else if (nbytes == 0) {
        _sendOnDone();
    } else if (_onReceive != NULL) {
        _onReceive(*this, std::string(buf));
    } else {
        _sendOnError(TcpSocketError("onReceive is null"));
    }
    return (1);
}

void TcpSocket::listen(void (*onReceive)(TcpSocket socket, std::string message),
                    void (*onDone)(TcpSocket socket),
                    void (*onError)(TcpSocket socket, TcpSocketError error)) {
    _onReceive = onReceive;
    _onError = onError;
    _onDone = onDone;
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    int ret_thread;
    ret_thread = pthread_create(&_thread, NULL,  threadRead, this);
    if (ret_thread < 0) {
        _sendOnError(TcpSocketError("pthread failed, try without thread"));
        threadRead(this);
    }
#else
    threadRead(this);
#endif
}

void TcpSocket::wait() {
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_join(_thread, NULL);
#endif
}

void TcpSocket::close() {
    _open = false;
    ::close(_descriptor);
}

void TcpSocket::destroy() {
    delete _ptr;
}

bool TcpSocket::isOpen() const {
    return (_open);
}

int TcpSocket::getFd() const {
    return (_descriptor);
}

void* TcpSocket::threadRead(void* data) {
    TcpSocket* socket = reinterpret_cast<TcpSocket*>(data);
    fd_set read_fd_set, active_fd_set;
    FD_ZERO(&read_fd_set);
    FD_SET(socket->_descriptor, &read_fd_set);
    try {
        while (socket->_open) {
            active_fd_set = read_fd_set;
            if (select(FD_SETSIZE, &active_fd_set, NULL, NULL, NULL) == -1) {
                if (socket->_open) {
                    socket->_sendOnError(TcpSocketError("select error"));
                }
            } else if (FD_ISSET(socket->_descriptor, &active_fd_set)) {
                if (socket->_read() == -1) {
                    socket->_sendOnError(TcpSocketError("read error"));
                } else {
                    FD_CLR(0, &active_fd_set);
                }
            }
        }
    }
    catch (TcpSocketError error) {
        socket->_sendOnError(error);
    }
    return (NULL);
}

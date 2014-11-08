//
//  HttpServer.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "./ServerSocket.h"

ServerSocketError::ServerSocketError(std::string message)
: Error("HttpServerError"), _message(message) {}

const std::string ServerSocketError::toString() {
    return (getType() + ": " + _message);
}

ServerSocket::ServerSocket() : RCObject("HttpServer") {
    _desriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (_desriptor == -1) {
        throw ServerSocketError("socket return -1");
    }
}

ServerSocket::~ServerSocket() {}

ServerSocket ServerSocket::bind(std::string address, Number<int> port) {
    struct sockaddr_in server_addr;
    ServerSocket* hs = new ServerSocket();

    hs->_address = address;
    hs->_port = port.getNumber();

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(hs->_port);
    if (::bind(hs->_desriptor,
               (struct sockaddr *) &server_addr,
               sizeof(server_addr)) == -1) {
        throw ServerSocketError("bind return -1");
    }
    hs->_ptr = hs;
    bzero(&server_addr, sizeof(server_addr));
    return (*hs);
}

void ServerSocket::sendOnError(ServerSocketError sse) const {
    if (_onError != NULL) {
        _onError(*this, sse);
    } else {
        Logger::root->log(Level::WARNING, sse.toString());
    }
}

void ServerSocket::listen(void (*onConnexion)(const ServerSocket& ss,
                                              Socket* socket),
                          void (*onError)(const ServerSocket& ss,
                                          const ServerSocketError sse)) {
    _onConnexion = onConnexion;
    _onError = onError;

    _isOpen = true;
    ::listen(_desriptor, 10);
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    int ret_thread;
    ret_thread = pthread_create(&_thread, NULL, threadRead, this);
    if (ret_thread < 0) {
        sendOnError(ServerSocketError("pthread failed, try without thread"));
        threadRead(this);
    }
#else
    threadRead(this);
#endif
}

int ServerSocket::getDescriptor() const {
    return (_desriptor);
}

void ServerSocket::wait() {
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_join(_thread, NULL);
#endif
}

void ServerSocket::close() {
    ::close(_desriptor);
}

void ServerSocket::destroy() {
    delete _ptr;
}

void ServerSocket::shutdown() {
    _isOpen = false;
    Socket* socket = Socket::connect(_address, Number<int>(_port));
    socket->close();
    socket->destroy();
}

void* ServerSocket::threadRead(void* data) {
    ServerSocket* ss = reinterpret_cast<ServerSocket*>(data);
    struct sockaddr_in client_addr;
    socklen_t  client_len = sizeof(client_addr);
    int client_descriptor;
    char buf[INET_ADDRSTRLEN];
    while (ss->_isOpen) {
        bzero(&client_addr, sizeof(client_addr));
        bzero(buf, sizeof(buf));
        client_descriptor = accept(ss->getDescriptor(),
                                   (struct sockaddr *)&client_addr,
                                   &client_len);
        if (client_descriptor == -1) {
            ss->sendOnError(ServerSocketError("accept return -1"));
        } else if (ss->_isOpen) {
            if (getpeername(client_descriptor,
                            (struct sockaddr *)&client_addr,
                            &client_len) == -1) {
                ss->sendOnError(ServerSocketError("getpeername return -1"));
            } else {
                inet_ntop(AF_INET, &client_addr.sin_addr, buf, sizeof buf);
            }
            Number<int>* fd = new Number<int>(client_descriptor);
            Number<int>* client_port;
            client_port = new Number<int>(ntohs(client_addr.sin_port));
            Logger::root->log(Level::INFO,
                              "nouveau client avec address: " +
                              std::string(buf) + " et le port: " +
                              client_port->toString() + " et fd: " +
                              fd->toString(), true);
            delete fd;
            delete client_port;
            Socket* socket = Socket::fromServerSocket(client_descriptor,
                                                      std::string(buf),
                                                      client_port->getNumber());
            ss->_onConnexion(*ss, socket);
        } else {
            ::close(client_descriptor);
        }
    }
    return (NULL);
}

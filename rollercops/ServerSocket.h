//
//  HttpServer.h
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#pragma once
#ifndef ROLLERCOPS_SERVERSOCKET_H_
#define ROLLERCOPS_SERVERSOCKET_H_

# include <string>
# include <strings.h>
# include <vector>
#  include <pthread.h>

# if defined(__linux) || defined(__unix) || defined(__APPLE__)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <pthread.h>
# endif

# include "./RCObject.h"
# include "./Error.h"
# include "./Number.h"
# include "./Logging.h"
# include "./TcpSocket.h"

class TcpSocket;

class ServerSocketError : protected Error {
 private:
    std::string _message;

 public:
    explicit ServerSocketError(std::string message);
    virtual const std::string toString();
};

class ServerSocket : protected RCObject {
 private:
    int _desriptor;
    std::string _address;
    int _port;
    bool _isOpen;
    ServerSocket* _ptr;
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_t _thread;
#endif

    ServerSocket();

    std::vector<TcpSocket*> _clients;

    void (*_onConnexion)(ServerSocket ss, TcpSocket* socket);
    void (*_onError)(ServerSocket ss, const ServerSocketError sse);

    void sendOnError(ServerSocketError sse) const;

 public:
    ~ServerSocket();

    static ServerSocket bind(std::string address, Number<int> port);
    static void *threadRead(void* ss);

    int getDescriptor() const;

    void listen(void (*onConnexion)(ServerSocket ss, TcpSocket* socket),
                void (*onError)(ServerSocket ss,
                                const ServerSocketError sse) = NULL);

    void wait();

    void clientLeave(TcpSocket* socket);

    void shutdown();
    void close();
    void destroy();
};

#endif  // ROLLERCOPS_SERVERSOCKET_H_

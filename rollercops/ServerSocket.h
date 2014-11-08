//
//  HttpServer.h
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_SERVERSOCKET_H_
#define ROLLERCOPS_SERVERSOCKET_H_

# include <string>

# if defined(__linux) || defined(__unix) || defined(__APPLE__)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <pthread.h>
# endif

# include "./RCObject.h"
# include "./Error.h"
# include "./Socket.h"
# include "./Number.h"

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

    void (*_onConnexion)(const ServerSocket& ss, Socket* socket);
    void (*_onError)(const ServerSocket& ss, const ServerSocketError sse);

    void sendOnError(ServerSocketError sse) const;

 public:
    ~ServerSocket();

    static ServerSocket bind(std::string address, Number<int> port);
    static void *threadRead(void* ss);

    int getDescriptor() const;

    void listen(void (*onConnexion)(const ServerSocket& ss,
                                    Socket* socket),
                void (*onError)(const ServerSocket& ss,
                                const ServerSocketError sse) = NULL);

    void wait();

    void shutdown();
    void close();
    void destroy();
};

#endif  // ROLLERCOPS_SERVERSOCKET_H_

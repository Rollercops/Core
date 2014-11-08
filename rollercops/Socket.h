//
//  Socket.h
//  logging
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_SOCKET_H_
#define ROLLERCOPS_SOCKET_H_

#include <string>

#include "./Number.h"
#include "./Logging.h"
#include "./Error.h"

# if defined(_WIN32) || defined(_WIN64)
#  include <winsock2.h>
#  pragma comment(lib, "Ws2_32.lib")
# elif defined(linux) || defined(__APPLE__)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <unistd.h> /* close */
#  include <netdb.h> /* gethostbyname */
#  include <pthread.h>
#  define INVALID_SOCKET -1
#  define closesocket(s) close(s)
// use -lws_32 compilation option
# endif

class SocketError : public Error {
 private:
    std::string _message;

 public:
    explicit SocketError(std::string message);
    virtual std::string toString();
};

class Socket {
 private:
    int _descriptor;
    std::string _address;
    int _port;
    bool _v6Only;
    bool _open;
    pthread_t _thread;

    Socket* _ptr;

    void (*_onReceive)(const Socket& socket, std::string message);
    void (*_onError)(const Socket& socket, SocketError error);
    void (*_onDone)(Socket& socket);

    Socket();

 public:
    static Socket& connect(std::string address,
                           Number<int> port,
                           bool v6Only = false);
    ~Socket();

    bool write(std::string message) const;
    void listen(void (*onReceive)(const Socket& socket, std::string message),
                void (*onClose)(Socket& socket) = NULL,
                void (*onError)(const Socket& socket,
                                SocketError error) = NULL);
    void close();
    int read();
    void wait();
    void destroy();

    void sendOnError(SocketError error) const;
    void sendOnClose();
    bool isOpen() const;
    int getFd() const;
};

void *threadRead(void* socket);

#endif  // ROLLERCOPS_SOCKET_H_

//
//  Socket.h
//  Rollercops
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_SOCKET_H_
#define ROLLERCOPS_SOCKET_H_

#include <string>

#include "./Logging.h"
#include "./Error.h"
#include "./RCObject.h"

# if defined(_WIN32) || defined(_WIN64)
#  include <winsock2.h>
#  pragma comment(lib, "Ws2_32.lib")
# elif defined(__linux) || defined(__unix) || defined(__APPLE__)
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

class SocketError : protected Error {
 private:
    std::string _message;

 public:
    explicit SocketError(std::string message);
    virtual std::string toString();
};

class Socket : protected RCObject {
 private:
    int _descriptor;
    std::string _address;
    int _port;
    bool _v6Only;
    bool _open;
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_t _thread;
#endif

    Socket* _ptr;

    void (*_onReceive)(Socket socket, std::string message);
    void (*_onError)(Socket socket, SocketError error);
    void (*_onDone)(Socket socket);

    Socket();
    Socket(int descriptor, std::string address, int port);

 public:
    static Socket* connect(std::string address,
                           Number<int> port,
                           bool v6Only = false);
    static Socket* fromServerSocket(int fd, std::string address, int port);

    ~Socket();

    bool write(std::string message);
    void listen(void (*onReceive)(Socket socket, std::string message),
                void (*onClose)(Socket socket) = NULL,
                void (*onError)(Socket socket,
                                SocketError error) = NULL);
    void close();
    int read();
    void wait();
    void destroy();

    void sendOnError(SocketError error);
    void sendOnClose();
    bool isOpen() const;
    int getFd() const;
};

void *threadRead(void* socket);

#endif  // ROLLERCOPS_SOCKET_H_

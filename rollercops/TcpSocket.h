//
//  TcpSocket.h
//  Rollercops
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_TCPSOCKET_H_
#define ROLLERCOPS_TCPSOCKET_H_

# include <string>
# include <strings.h>
# include "./Logging.h"
# include "./Error.h"
# include "./RCObject.h"
# include "./ServerSocket.h"
# include <stdio.h>
# include <string.h>


# if defined(_WIN32) || defined(_WIN64)
#  include <winsock2.h>
#  pragma comment(lib, "Ws2_32.lib")
# elif defined(__linux) || defined(__unix) || defined(__APPLE__)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <errno.h>
#  include <unistd.h> /* close */
#  include <netdb.h> /* gethostbyname */
#  include <pthread.h>
# endif

class ServerSocket;

class TcpSocketError : protected Error {
 private:
    std::string _message;

 public:
    explicit TcpSocketError(std::string message);
    virtual std::string toString();
};

class TcpSocket : protected RCObject {
 private:
    int _descriptor;
    std::string _address;
    int _port;
    bool _open;
#if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_t _thread;
#endif

    TcpSocket* _ptr;
    ServerSocket* _parent;

    void (*_onReceive)(TcpSocket socket, std::string message);
    void (*_onError)(TcpSocket socket, TcpSocketError error);
    void (*_onDone)(TcpSocket socket);

    TcpSocket();
    TcpSocket(int descriptor, std::string address, int port);

    void _sendOnError(TcpSocketError error);
    void _sendOnDone();
    int _read();

 public:
    static TcpSocket* connect(std::string address, Number<int> port);
    static TcpSocket* fromServerSocket(int fd, std::string address,
                                       int port, ServerSocket* ss);
    static void *threadRead(void* socket);

    ~TcpSocket();

    int write(std::string message);
    void listen(void (*onReceive)(TcpSocket socket, std::string message),
                void (*onDone)(TcpSocket socket) = NULL,
                void (*onError)(TcpSocket socket, TcpSocketError error) = NULL);

    void wait();
    void close();
    void destroy();

    bool isOpen() const;
    int getFd() const;
};


#endif  // ROLLERCOPS_TCPSOCKET_H_

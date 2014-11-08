//
//  main.cpp
//  main
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <stdio.h>

#include <string>

#include "./Logging.h"
#include "./Socket.h"
#include "./DateTime.h"
#include "./number.h"
#include "./ServerSocket.h"

int nbClient = 0;

void socketOnReceive(Socket socket, std::string message) {
    socket.write("Hello server\n");
    Logger::root->log(Level::INFO, message, false);
}

void socketOnDone(Socket socket) {
    nbClient--;
    Logger::root->log(Level::INFO,
                      "un client c'est deco: " +
                      Number<int>(socket.getFd()).toString());
    Logger::root->log(Level::INFO,
                      "nous avons maintenant: " +
                      Number<int>(nbClient).toString());
}

void trySocker() {
    try {
        Socket* socket = Socket::connect("127.0.0.1", Number<int>(8888));
        Logger::root->log(Level::INFO, "We are connected");
        socket->listen(socketOnReceive, socketOnDone);

        socket->write("C'est bien asynchrone\n");

        socket->wait();
        socket->destroy();
    } catch (SocketError se) {
        Logger::root->log(Level::SEVERE, se.toString());
    }
}

void tryNumber() {
    Number<int> myInt(987667);
    Logger::root->log(Level::INFO, myInt.toString());

    Number<float> myFloat(1.5);
    Logger::root->log(Level::INFO, myFloat.toString());

    myInt = myFloat.toInt();

    Logger::root->log(Level::INFO, myInt.toString());
}

void serverSocketOnReceive(const ServerSocket& ss, Socket* socket) {
    nbClient++;
    Logger::root->log(Level::INFO,
                      "nous avons maintenant: " +
                      Number<int>(nbClient).toString());
    socket->listen(socketOnReceive, socketOnDone);
}

void exitConsole() {
    char buf[512];
    read(0, buf, sizeof(buf));
    std::string  exit(buf);
    if (exit != "shutdown\n") {
        exitConsole();
    }
}

void tryServerSocket() {
    try {
        ServerSocket ss = ServerSocket::bind("127.0.0.1", Number<int>(8888));
        ss.listen(serverSocketOnReceive);
        Logger::root->log(Level::INFO,
                          "Pour quitter taper shutdown puis Entrer");

        exitConsole();
        Logger::root->log(Level::SHOUT, "Server shutdown");

        ss.wait();

        ss.shutdown();
        ss.close();
        ss.destroy();
    } catch (ServerSocketError sse) {
        Logger::root->log(Level::SEVERE, sse.toString());
    }
}

int main() {
    tryServerSocket();

    //  IMPORTANT: pensez a detruire tous les loggers grace a destroyAllLogger
    Logger::destroyAllLogger();
    return (0);
}

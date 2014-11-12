//
//  main.cpp
//  main
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

# include <stdio.h>

# include <string>
# include <strings.h>

# include "./Logging.h"
# include "./DateTime.h"
# include "./Number.h"
# include "./ServerSocket.h"
# include "./TcpSocket.h"

# include "./Num.h"

int nbClient = 0;

void socketOnReceive(TcpSocket socket, std::string message) {
    Logger::root->log(Level::INFO, message, false);
    if (message == "ping\n") {
        socket.write("ping\n");
    } else {
        socket.write("pong\n");
    }
}

void socketOnDone(TcpSocket socket) {
    nbClient--;
    Logger::root->log(Level::INFO,
                      "un client c'est deco: " +
                      Number<int>(socket.getFd()).toString());
    Logger::root->log(Level::INFO,
                      "nous avons maintenant: " +
                      Number<int>(nbClient).toString());
}

void trySocket() {
    try {
        TcpSocket* socket = TcpSocket::connect("127.0.0.1", Number<int>(8888));
        Logger::root->log(Level::INFO, "We are connected");
        socket->listen(socketOnReceive, socketOnDone);

        socket->write("C'est bien asynchrone\n");

        socket->wait();
        socket->destroy();
    } catch (TcpSocketError se) {
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

void serverSocketOnReceive(ServerSocket ss, TcpSocket* socket) {
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

        ss.shutdown();
        ss.wait();

        ss.close();
        ss.destroy();
    } catch (ServerSocketError sse) {
        Logger::root->log(Level::SEVERE, sse.toString());
    }
}

int main() {
    Int j = Int(12);
    Num* i = &j;
    
    Logger::root->log(Level::INFO, i->addPrefix(Int(3), Int(0)));

//    tryServerSocket();

    //  IMPORTANT: pensez a detruire tous les loggers grace a destroyAllLogger
    Logger::destroyAllLogger();
    return (0);
}

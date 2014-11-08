#include "Logging.h"
#include "Socket.h"
#include "DateTime.h"
#include "number.h"

void onReceive(const Socket& socket, std::string message) {
    socket.write("Hello server\n");
    Logger::root->log(Level::INFO, message, false);
}

void onDone(Socket& socket) {
    Logger::root->log(Level::INFO, "Server close the socket");
}

int	main() {
    try {
        Socket socket = Socket::connect("127.0.0.1", Number<int>(8888));
        Logger::root->log(Level::INFO, "We are connected");
        socket.listen(onReceive, onDone);

        socket.write("C'est bien asynchrone\n");

        socket.wait();
        socket.destroy();
    } catch (SocketError se) {
        Logger::root->log(Level::SEVERE, se.toString());
    }

    Number<int> myInt(987667);
    Logger::root->log(Level::INFO, myInt.toString());
    
    Number<float> myFloat(1.5);
    Logger::root->log(Level::INFO, myFloat.toString());

    myInt = myFloat.toInt();
    
    Logger::root->log(Level::INFO, myInt.toString());
    
    //  IMPORTANT: pensez a detruire tous les loggers grace a destroyAllLogger
    Logger::destroyAllLogger();
    return (0);
}

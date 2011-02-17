#include <QtCore/QCoreApplication>
#include <QtNetwork/QUdpSocket>
#include <client.h>
#include <server.h>
#include <sstream>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char option;
    std::string portIdString;
    int portId;

    std::cout << "Please enter a valid port number:";
    std::getline(std::cin, portIdString);
    std::stringstream stream(portIdString);
    stream >> portId;

    std::cout << "Would you like to be a server [S] or a client [C]: ";
    std::cin >> option;

    if (option == 'S' || option == 's')
    {
        HEX::Server server;
        server.initSocket(portId);
    }
    else if (option == 'C' || option == 'c')
    {
        HEX::Client client;
        client.initSocket(portId);
    }

    return a.exec();
}

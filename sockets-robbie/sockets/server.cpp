#include "server.h"

HEX::Server::Server()
{
    socket = 0;
}

HEX::Server::~Server()
{
    delete socket;
}

void HEX::Server::initSocket(int portNumber)
{
    delete socket;
    socket = new QUdpSocket(this);
    std::cout << "Initializing Server with PortId " << portNumber << std::endl;
    socket->bind(QHostAddress::LocalHost, portNumber);
}

void HEX::Server::sendMessage()
{
    if (socket) {
	socket->write("Hello", 10);
    }
}

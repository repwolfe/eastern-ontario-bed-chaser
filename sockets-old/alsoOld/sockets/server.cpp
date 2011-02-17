#include "server.h"

Server::Server()
{
    socket = 0;
}

Server::~Server()
{
    delete socket;
}

void Server::initSocket(int portNumber)
{
    delete socket;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, portNumber);
}

void Server::sendMessage()
{
    if (socket) {
	socket->write("Hello", 10);
    }
}

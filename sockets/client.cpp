#include "client.h"
#include <iostream>
#include <sstream>

HEX::Client::Client()
    : _num(1)
{
    socket = 0;
}

HEX::Client::~Client()
{
    delete socket;
}

void HEX::Client::initSocket(QString& ip, int portNumber)
{
    delete socket;
    socket = new QUdpSocket(this);
    std::cout << "Initializing Client with PortId " << portNumber << std::endl;
    _ip = ip;
    _portNumber = portNumber;
}

void HEX::Client::sendMessage()
{
    if (socket) {
        std::string message = "Hello ";
	std::stringstream stream;
	stream << message << _num;
	++_num;
	std::cout << "Sending message " << stream.str() << std::endl;
	socket->writeDatagram(QByteArray(stream.str().c_str()), QHostAddress(_ip), _portNumber);
	socket->flush();
    }
}

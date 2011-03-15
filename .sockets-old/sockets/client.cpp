#include "client.h"
#include <iostream>

HEX::Client::Client()
{
    socket = 0;
}

HEX::Client::~Client()
{
    delete socket;
}

void HEX::Client::initSocket(int portNumber)
{
    delete socket;
    socket = new QUdpSocket(this);
    std::cout << "Initializing Client with PortId " << portNumber << std::endl;
    socket->bind(QHostAddress::LocalHost, portNumber);
}

void HEX::Client::readMessage()
{
    if (socket) {
	while (socket->hasPendingDatagrams()) {
	    QByteArray datagram;
	    datagram.resize(socket->pendingDatagramSize());
	    QHostAddress sender;
	    quint16 senderPort;
	    socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

	    _processTheDatagram(datagram);
	}
    }
}

void HEX::Client::_processTheDatagram(QByteArray& datagram)
{
    char output[datagram.size()];
    for (int i = 0; i < datagram.size(); ++i) {
	output[i] = datagram.at(i);
    }
    std::cout << output << std::endl;
}

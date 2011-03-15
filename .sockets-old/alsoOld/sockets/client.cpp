#include "client.h"
#include <iostream>

Client::Client()
{
    socket = 0;
}

Client::~Client()
{
    delete socket;
}

void Client::initSocket(int portNumber)
{
    delete socket;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, portNumber);
}

void Client::readMessage()
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

void Client::_processTheDatagram(QByteArray& datagram)
{
    char output[datagram.size()];
    for (int i = 0; i < datagram.size(); ++i) {
	output[i] = datagram.at(i);
    }
    std::cout << output << std::endl;
}

#include "server.h"

HEX::Server::Server()
{
    _numReceived = 0;
    socket = 0;
}

HEX::Server::~Server()
{
    delete socket;
}



bool HEX::Server::initSocket(int portNumber)
{
    delete socket;
    socket = new QUdpSocket(this);
    std::cout << "Initializing Server with PortId " << portNumber << std::endl;
    bool succeed = socket->bind(portNumber);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    if (!succeed) { qDebug() << "Server connection failed"; }
    return succeed;
}

void HEX::Server::readMessage()
{
    if (socket) {
	while (socket->hasPendingDatagrams()) {
	    QByteArray datagram;
	    datagram.resize(socket->pendingDatagramSize());
	    socket->readDatagram(datagram.data(), datagram.size());
	    _numReceived++;
	    _processTheDatagram(datagram);
	}
    }
}

void HEX::Server::_processTheDatagram(QByteArray& datagram)
{
    std::string output(datagram.data());
    std::cout << "Received message #" << _numReceived << " : " << output << std::endl;
}

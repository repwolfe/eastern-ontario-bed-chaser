#include "channelin.h"
#include "logger.h"
#include <QFile>

ChannelIn::ChannelIn()
{
    _socket = new QUdpSocket();
    QString location(":/comms/resources/comsConfig.txt");
    QFile myFile(location);
    if (!myFile.open(QIODevice::ReadOnly))
    {
        Logger::errorMessage("ChannelOut", "sendMessage()", "Failed to load list of ips at", location);
        return;
    }
    QTextStream t(&myFile);
    QString portNumber = t.readLine();

    _socket->bind(portNumber.toInt());
    connect(_socket, SIGNAL(readyRead()), SLOT(_readMessage()));
}

ChannelIn::~ChannelIn()
{
    delete _socket;
}

void ChannelIn::_readMessage()
{
    while (_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_socket->pendingDatagramSize());
	_socket->readDatagram(datagram.data(), datagram.size());

        _processTheDatagram(datagram);
    }
}

void ChannelIn::_processTheDatagram(QByteArray& datagram)
{
    /// @todo process it somehow
    Q_UNUSED(datagram);
}

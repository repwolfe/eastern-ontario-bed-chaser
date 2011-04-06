#include "channelout.h"
#include "logger.h"

#include <QFile>
#include <QStringList>

ChannelOut::ChannelOut()
{
    _socket = new QUdpSocket();
}

ChannelOut::~ChannelOut()
{
    delete _socket;
}

/**
 * Sends a message to all the ip addresses in the text file.
 *
 */
void ChannelOut::sendMessage(const QByteArray &datagram)
{
    QString location(":/comms/resources/comsConfig.txt");
    QStringList ips;
    QFile myFile(location);
    if (!myFile.open(QIODevice::ReadOnly))
    {
        Logger::errorMessage("ChannelOut", "sendMessage()", "Failed to load list of ips at", location);
        return;
    }
    QTextStream t(&myFile);
    QString portNumber = t.readLine();

    while (!t.atEnd())
    {
        ips << t.readLine();
    }

    foreach(QString ip, ips)
    {
        if (_socket->writeDatagram(datagram, QHostAddress(ip), portNumber.toInt()) == -1)
        {
            // It failed, log the reason
            Logger::errorMessage("ChannelOut", "sendMessage()",
                                 ip.toStdString() + ": Failed to send message because:", _socket->errorString());
            Logger::errorMessage("ChannelOut", "sendMessage()",
                                 ip.toStdString() + ": Error sending message:", QString(datagram));
        }
    }

    myFile.close();
}

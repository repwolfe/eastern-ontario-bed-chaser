#ifndef CHANNELOUT_H
#define CHANNELOUT_H

#include <QUdpSocket>

/**
 * @brief Responsible for connections to other systems
 *
 * Loads a list of IP addresses to send messages which meet
 * the decided communication protocol. Sends these messages
 * via UDP sockets.
 *
 * This class is part of the Communication subsystem described in D2.
 */
class ChannelOut
{
public:
    ChannelOut();
    ~ChannelOut();

    void sendMessage(const QByteArray& datagram);

private:
    QUdpSocket* _socket;
};

#endif // CHANNELOUT_H

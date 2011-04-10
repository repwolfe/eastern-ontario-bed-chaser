#ifndef CHANNELIN_H
#define CHANNELIN_H

#include <QUdpSocket>

/**
 * @brief Used to listen for messages
 *
 * This class listens on a particular port waiting for messages
 * from other systems. Upon receiving a message, it is then processed
 *
 * This class is in the subsystem Communication described in D2.
 */
class ChannelIn : public QObject
{
    Q_OBJECT
public:
    ChannelIn();
    ~ChannelIn();

signals:
    void processTheMessage(QByteArray& datagram);

private slots:
    void _readMessage();

private:
    QUdpSocket* _socket;
};

#endif // CHANNELIN_H

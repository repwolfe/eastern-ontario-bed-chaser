#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QUdpSocket>
#include <QObject>
#include <iostream>

namespace HEX {
class Server : QObject
{
    Q_OBJECT
public:
    Server();
    ~Server();

    bool initSocket(int portNumber);

public slots:
    void readMessage();

private:
    void _processTheDatagram(QByteArray& datagram);

    QUdpSocket* socket;

};
}

#endif // SERVER_H

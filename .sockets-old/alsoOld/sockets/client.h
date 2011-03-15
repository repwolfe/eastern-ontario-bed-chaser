#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QUdpSocket>

class Client : QObject
{
public:
    Client();
    ~Client();

    void initSocket(int portNumber);
    void readMessage();

private:
    void _processTheDatagram(QByteArray& datagram);

    QUdpSocket* socket;
};

#endif // CLIENT_H

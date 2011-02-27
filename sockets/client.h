#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QUdpSocket>
#include <QObject>
#include <iostream>

namespace HEX {
class Client : QObject
{

public:
    Client();
    ~Client();

    bool initSocket(QString& ip, int portNumber);
    void sendMessage();

private:
    int _num;
    QString _ip;
    int _portNumber;
    QUdpSocket* socket;
};
}

#endif // CLIENT_H

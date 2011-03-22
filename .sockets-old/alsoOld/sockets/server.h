#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QUdpSocket>

class Server : QObject
{
public:
    Server();
    ~Server();

    void initSocket(int portNumber);
    void sendMessage();

private:

    QUdpSocket* socket;

};

#endif // SERVER_H
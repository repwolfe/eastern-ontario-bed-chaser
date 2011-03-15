#include <QtCore/QCoreApplication>
#include <QtNetwork/QUdpSocket>
#include <iostream>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string ip;
    QUdpSocket* socket;

    std::cout << "Please enter a valid ip address, -1 to quit:" << std::endl;
    std::getline(std::cin, ip);

    return a.exec();
}

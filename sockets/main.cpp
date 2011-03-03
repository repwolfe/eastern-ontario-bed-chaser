#include <QtCore/QCoreApplication>
#include <QtNetwork/QUdpSocket>
#include <QFile>
#include <client.h>
#include <server.h>
#include <sstream>
#include <QtTest/QTest>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char option;
    HEX::Server server;
    HEX::Client client;

    QFile myFile("info");	// Load info
    QString port, connectIp;

    std::cout << "Which computer # are you [1-2]? :";
    std::cin >> option;

    if (!myFile.open(QIODevice::ReadOnly))
    {
        return -1;
    }

    QTextStream t( &myFile );        // use a text stream

    port = t.readLine();
    if (!server.initSocket(port.toInt()))
    {
	std::cout << "Failed to connect server to port " << port.toStdString();
	return -1;
    }

    if (option == '1')
    {
	t.readLine();	    // connect to the second ip, skip the first one
    }

    connectIp = t.readLine();

    myFile.close();

    client.initSocket(connectIp, port.toInt());

    while (true)
    {
	client.sendMessage();
	QTest::qWait(500);
    }

    return a.exec();
}

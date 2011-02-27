#include <QtCore/QCoreApplication>
#include <QtNetwork/QUdpSocket>
#include <QFile>
//#include <QIODevice>
#include <client.h>
#include <server.h>
#include <sstream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char option;
    HEX::Server server;
    HEX::Client client;

    QFile myFile("info");	// Load info
    QString port, connectIp;
    if (!myFile.open(QIODevice::ReadOnly))
    {
	return -1;
    }

    QTextStream t( &myFile );        // use a text stream
    port = t.readLine();
    t.readLine();   // ignore this line
    connectIp = t.readLine();
    myFile.close();

    std::cout << "Would you like to be a server [S] or a client [C]: ";
    std::cin >> option;

    if (option == 'S' || option == 's')
    {

	if (server.initSocket(port.toInt()))
	{

	}
	else
	{
	    std::cout << "Failed to connect server to port " << port.toStdString();
	}

    }
    else if (option == 'C' || option == 'c')
    {
	if (client.initSocket(connectIp, port.toInt()))
	{
	    while (true)
	    {
		client.sendMessage();
	    }
	}
	else
	{
	    std::cout << "Failed to connect client to port " << port.toStdString();
	}
    }

    return a.exec();
}

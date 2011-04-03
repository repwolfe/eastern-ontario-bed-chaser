#include "communicationsendinterface.h"

CommunicationSendInterface::CommunicationSendInterface(SendMessageControl& sendMessage)
    : _sendMessage(sendMessage)
{
    _channelOut = new ChannelOut();
    connect(&_sendMessage, SIGNAL(sendQByte(QByteArray&)), SLOT(sendMessage(QByteArray&)));
}

CommunicationSendInterface::~CommunicationSendInterface()
{
    delete _channelOut;
}

void CommunicationSendInterface::sendMessage(QByteArray& data)
{
    _channelOut->sendMessage(data);
}

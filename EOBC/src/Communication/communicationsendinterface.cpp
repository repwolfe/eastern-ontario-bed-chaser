#include "communicationsendinterface.h"

CommunicationSendInterface::CommunicationSendInterface()
{
    _channelOut = new ChannelOut();
}

CommunicationSendInterface::~CommunicationSendInterface()
{
    delete _channelOut;
}

void CommunicationSendInterface::sendMessage(QByteArray& data)
{
    _channelOut->sendMessage(data);
}

#include "communicationreceiveinterface.h"

CommunicationReceiveInterface::CommunicationReceiveInterface()
{
    _channelIn = new ChannelIn();
    connect(_channelIn, SIGNAL(processTheMessage(QByteArray&)), SLOT(_processTheMessage(QByteArray&)));
}

CommunicationReceiveInterface::~CommunicationReceiveInterface()
{
    delete _channelIn;
}

void CommunicationReceiveInterface::_processTheMessage(QByteArray& data)
{
    emit processTheMessage(data);
}

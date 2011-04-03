#include "communicationsendinterface.h"

CommunicationSendInterface::CommunicationSendInterface(SendMessageControl& sendMessage)
    : _sendMessage(sendMessage)
{
    //connect(&_sendMessage, SIGNAL())
}

void CommunicationSendInterface::sendMessage(QByteArray& data)
{

}

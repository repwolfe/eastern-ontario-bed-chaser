#include "sendgetdatainterface.h"

SendGetDataInterface::SendGetDataInterface(SendMessageControl& sendMsgControl,QObject *parent) :
    QObject(parent)
{
    Q_UNUSED(sendMsgControl);
}

void SendGetDataInterface::sendFacility(Facility* f)
{

}

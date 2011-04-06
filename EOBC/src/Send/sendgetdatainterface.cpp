#include "sendgetdatainterface.h"

SendGetDataInterface::SendGetDataInterface(SendMessageControl& sendMsgControl,QObject *parent) :
    QObject(parent), _sendMsgControl(sendMsgControl)
{

}

void SendGetDataInterface::sendFacility(Facility* f)
{
    _sendMsgControl.addFacilities(false,f->getAreaThisIsIn()->getAreaId(),f);
}

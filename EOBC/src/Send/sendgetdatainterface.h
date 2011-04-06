#ifndef SENDGETDATAINTERFACE_H
#define SENDGETDATAINTERFACE_H

#include <QObject>
#include "sendmessagecontrol.h"

class SendGetDataInterface : public QObject
{
    Q_OBJECT
public:
    explicit SendGetDataInterface(SendMessageControl& sendMsgControl,QObject *parent = 0);

signals:

public slots:

};

#endif // SENDGETDATAINTERFACE_H

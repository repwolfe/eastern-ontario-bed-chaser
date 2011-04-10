#ifndef COMMUNICATIONRECEIVEINTERFACE_H
#define COMMUNICATIONRECEIVEINTERFACE_H

#include "channelin.h"

class CommunicationReceiveInterface : public QObject
{
    Q_OBJECT
public:
    CommunicationReceiveInterface();
    ~CommunicationReceiveInterface();

signals:
    void processTheMessage(QByteArray& datagram);

public slots:
    void _processTheMessage(QByteArray& datagram);

private:
    ChannelIn* _channelIn;
};

#endif // COMMUNICATIONRECEIVEINTERFACE_H

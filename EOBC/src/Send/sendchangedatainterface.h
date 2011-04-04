#ifndef SENDCHANGEDATAINTERFACE_H
#define SENDCHANGEDATAINTERFACE_H

#include <QObject>
#include "sendmessagecontrol.h"

/**
 * @todo description
 *
 * @todo traceability
 */
class SendChangeDataInterface : public QObject
{
    Q_OBJECT
public:
    SendChangeDataInterface(SendMessageControl& sendMessage);

    void addPatients(bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p);
    void deletePatients(bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p);

signals:

public slots:

private:
    SendMessageControl& _sendMessage;

};

#endif // SENDCHANGEDATAINTERFACE_H

#ifndef SENDCHANGEDATAINTERFACE_H
#define SENDCHANGEDATAINTERFACE_H

#include <QObject>
#include "sendmessagecontrol.h"

/**
 * @brief Interface between the Send and ChangeData subsystems
 *
 * Provides link necessary to allow ChangeData to send out messages
 * of the changes
 *
 * This class is part of the Send subsystem described in D2.
 */
class SendChangeDataInterface : public QObject
{
    Q_OBJECT
public:
    SendChangeDataInterface(SendMessageControl& sendMessage);

    void addPatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p);
    void addPatients(bool remote, Area* anArea, QLinkedList<Patient*> p);
    void deletePatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p);
    void deletePatients(bool remote, Area* anArea, QLinkedList<Patient*> p);
    void addBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds);
    void removeBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds);
    void addFacilities(bool remote,ID id, Facility* aFacility);

signals:

public slots:

private:
    SendMessageControl& _sendMessage;

};

#endif // SENDCHANGEDATAINTERFACE_H

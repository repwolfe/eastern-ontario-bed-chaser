#ifndef SENDMESSAGECONTROL_H
#define SENDMESSAGECONTROL_H

#include "area.h"
#include <QFile>
#include <QLinkedList>
#include <QtXml/qdom.h>
#include "logger.h"
#include "convenience.h"
#include "communicationsendinterface.h"


/**
 * @brief Creates messages to be sent to other EOBC nodes
 *
 * Turns model objects into XML tags
 *
 * This class is part of the Send subsystem described in D2.
 */
class SendMessageControl
{
public:
    SendMessageControl(CommunicationSendInterface& communication);
    //void addPatient(bool remote, Area* anArea, Facility* aFacility, Patient* p);
    void addPatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*>& p);
    void addPatients(bool remote, Area* anArea, QLinkedList<Patient*>& p);

    void addBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds);
    void removeBeds(bool remote,Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds);

    void deletePatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*>& p);
    void deletePatients(bool remote, Area* anArea, QLinkedList<Patient*>& p);

    void addFacilities(bool remote,ID id, Facility* aFacility);

    void rebuild(Area* anArea, Facility* aFacility);
    void rebuild();
    //occupancy
    void request(Area* requestArea, Facility* requestFacility, QDate start, QDate finish );
    void request(Area* requestArea, Facility* requestFacility, QDate start);
    //waiting list
    void request(Area* requestArea, QDate start, QDate finish );
    void request(Area* requestArea, QDate start);
    //occupancy
    void response(Area* requestArea, Facility* requestFacility, QDate start, QDate finish );
    void response(Area* requestArea, Facility* requestFacility, QDate start);
    //waiting list
    void response(Area* requestArea, QDate start, QDate finish );
    void response(Area* requestArea, QDate start);

    void sendQByte(QByteArray &data);
private:
    void doStuffToPatients(QString str, bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p);
    void toXML(QDomDocument& doc,QDomElement* e, Area* anArea, Facility* aFacility, Patient* p);
    void toXML(QDomDocument& doc,QDomElement* e, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p);
    void toXML(QDomDocument& doc,QDomElement* e, Area* anArea, Facility* aFacility);
    void toXMLEmptyFacility(QDomDocument& doc,QDomElement* fac, Facility* aFacility); //Jp can change the name of this if he wants, doesnt fit his convention
    void toXML(QDomDocument& doc,QDomElement* e, Facility* aFacility);
    void toXML(QDomDocument& doc,QDomElement* e, Patient* p, bool inpatient);
    /// add beds to a facility
    void toXML(QDomDocument& doc,QDomElement* fac, Facility* aFacility, int deltaAC, int deltaCCC, int deltaLTC);

    CommunicationSendInterface& _communication;
};

#endif // SENDMESSAGECONTROL_H

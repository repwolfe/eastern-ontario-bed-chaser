#ifndef SENDMESSAGECONTROL_H
#define SENDMESSAGECONTROL_H

#include "area.h"
#include "QFile"
#include "QLinkedList"
#include <QtXml/qdom.h>
#include "../Common/logger.h"

class SendMessageControl
{
public:
    SendMessageControl();
    void addPatient(bool remote, Area* anArea, Facility* aFacility, Patient* p);
    void deletePatient(bool remote, Area* anArea, Facility* aFacility, Patient* p);
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
private:
    QDomElement toXML(Area* anArea, Facility* aFacility, Patient* p);
    QDomElement toXML(Area* anArea, Facility* aFacility);
    QDomElement toXML(Patient* p);
    QDomNode addThis(QDomNode addThis);
    QDomNode deleteThis(QDomElement deleteThis);
    QDomNode rebuildThis(QDomElement rebuildThis);
    QDomNode requestThis(QDomElement requestThis, QDate start, QDate finish);
    QDomNode requestThis(QDomElement requestThis, QDate start);
    QDomNode responseThis(QDomElement responseThis);
};

#endif // SENDMESSAGECONTROL_H

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
    QDomNode toXML(Area* anArea, Facility* aFacility, Patient* p);
    QDomNode toXML(Area* anArea, Facility* aFacility);

    QDomNode addThis(QDomNode addThis);
    QDomNode deleteThis(QDomNode deleteThis);
    QDomNode rebuildThis(QDomNode rebuildThis);
    QDomNode requestThis(QDomNode requestThis, QDate start, QDate finish);
    QDomNode requestThis(QDomNode requestThis, QDate start);
    QDomNode responseThis(QDomNode responseThis);
};

#endif // SENDMESSAGECONTROL_H

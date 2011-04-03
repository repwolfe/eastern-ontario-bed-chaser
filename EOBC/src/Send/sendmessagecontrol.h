#ifndef SENDMESSAGECONTROL_H
#define SENDMESSAGECONTROL_H

#include "area.h"
#include <QFile>
#include <QLinkedList>
#include <QtXml/qdom.h>
#include "../Common/logger.h"
#include "../Common/convenience.h"


/**
 * @brief Creates messages to be sent to other EOBC nodes
 *
 * Turns model objects into XML tags
 *
 * This class is part of the Send subsystem described in D2.
 */
class SendMessageControl : public QObject
{
    Q_OBJECT
public:
    SendMessageControl();
    //void addPatient(bool remote, Area* anArea, Facility* aFacility, Patient* p);
    void addPatients(bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p);
    void deletePatients(bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p);
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
signals:
    void sendQByte(QByteArray &data);
private:
    void doStuffToPatients(QString str, bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p);
    void toXML(QDomElement* e, Area* anArea, Facility* aFacility, Patient* p);
    void toXML(QDomElement* e, Area* anArea, Facility* aFacility, QList<Patient*> p);
    void toXML(QDomElement* e, Area* anArea, Facility* aFacility);
    void toXML(QDomElement* e, Facility* aFacility);
    void toXML(QDomElement* e, Patient* p, bool inpatient);

};

#endif // SENDMESSAGECONTROL_H

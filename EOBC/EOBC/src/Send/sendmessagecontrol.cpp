#include "sendmessagecontrol.h"

SendMessageControl::SendMessageControl(CommunicationSendInterface& communication)
    : _communication(communication)
{

}

/**
 * Helper function to the private methods, turns a Patient into an xml tag
 *
 * @param p the Patient that will be transformend into an XML tag
 *
 * @param e the element that patient will be returned in
 *
 * @param inpatient determines if the dateAdded or dateAdmitted attribut is set
 *
 */
void SendMessageControl::toXML(QDomDocument& doc,QDomElement* e,Patient* p, bool inpatient){
    Q_UNUSED(doc);
    e->setTagName("Patient");
    e->setAttribute("healthCardNumber", p->getHealthCardNumber());
    e->setAttribute("firstName", p->getFirstName());
    e->setAttribute("lastName", p->getLastName());
    e->setAttribute("reqCare", p->getRequiredCare());
    e->setAttribute("occCare", p->getOccupiedCare());
    if (inpatient){
        e->setAttribute("dateAdmitted", Convenience::toXML(p->getAdmissionDate()));
    }else{
        e->setAttribute("dateAdded", Convenience::toXML(p->getDatePlacedOnWaitingList()));
    }
}

void SendMessageControl::toXML(QDomDocument& doc,QDomElement* e, Area* anArea, Facility* aFacility, QLinkedList<Patient*> pList){
    QDomElement fac = doc.createElement("Facility");
   // fac.setTagName("Facility");
    fac.setAttribute("ID", aFacility->getFacilityId());

    foreach(Patient* patInList, pList ){
        QDomElement pat = doc.createElement("Patient");
        this->toXML(doc,&pat, patInList, true);
        fac.appendChild(pat);
    }



    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());

    e->appendChild(fac);
}

/**
 * Helper function to the public methods, turns a Patient into an xml tag
 *
 * @param p the Patient that will be transformend into an XML tag
 *
 * @param e the element that Area will be returned in
 *
 * @param aFacility the Facility that will be turned into a tag within the Area tag
 *
 * @param anArea the Area that will be turned into an XML tag
 *
 */
void SendMessageControl::toXML(QDomDocument& doc,QDomElement* e, Area* anArea, Facility* aFacility, Patient* p){
    QDomElement fac = doc.createElement("");
    fac.setTagName("Facility");
    fac.setAttribute("ID", aFacility->getFacilityId());
    QDomElement pat = doc.createElement("");
    this->toXML(doc,&pat, p, true);
    fac.appendChild(pat);

    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());

    e->appendChild(fac);

}
/**
 * Helper function to the public methods, returns a complete view of a facility
 *
 * @param e the element that Area will be returned in
 *
 * @param aFacility the Facility that will be turned into a tag within the Area tag
 *
 * @param anArea the Area that will be turned into an XML tag
 *
 */
void SendMessageControl::toXML(QDomDocument& doc,QDomElement* e, Area* anArea, Facility* aFacility){
    e->setTagName("Area");
    QDomElement fac = doc.createElement("Facility");
    this->toXML(doc,&fac, aFacility);

    e->setAttribute("ID", anArea->getAreaId());
    qDebug(fac.toDocument().toString().toAscii());
    e->appendChild(fac);

}

/**
 * Helper function to the private methods, returns a complete view of a facility
 *
 * @param fac the element that Area will be returned in
 *
 * @param aFacility the Facility that will be turned into an XML tag
 *
 */
void SendMessageControl::toXML(QDomDocument& doc,QDomElement* fac, Facility* aFacility){

    fac->setTagName("Facility");
    fac->setAttribute("ID", aFacility->getFacilityId());
    fac->setAttribute("LTC", aFacility->getNumBeds(EOBC::LTC));
    fac->setAttribute("AC", aFacility->getNumBeds(EOBC::AC));
    fac->setAttribute("CCC", aFacility->getNumBeds(EOBC::CCC));
    fac->setAttribute("name", aFacility->getFacilityName());
    fac->setAttribute("coordinateX", aFacility->getLocation().x());
    fac->setAttribute("coordinateY", aFacility->getLocation().y());

    PatientContainer * patients = aFacility->getPatientsForType(EOBC::LTC);
    if(patients->count() <= 0)
    {
        patients = aFacility->getPatientsForType(EOBC::AC);
        Patient* p;
        foreach(QString str, patients->keys()){
             p = patients->find(str).value();
	     QDomElement pat = doc.createElement("Patient");
             this->toXML(doc,&pat,p, true);
             fac->appendChild(pat);
        }

        patients = aFacility->getPatientsForType(EOBC::CCC);
        foreach(QString str, patients->keys()){
             p = patients->find(str).value();
	     QDomElement pat = doc.createElement("Patient");
             this->toXML(doc,&pat,p, true);
             fac->appendChild(pat);
        }
    }else {
        Patient* p;
        QDomElement pat;
        foreach(QString str, patients->keys()){
             p = patients->find(str).value();
             pat = doc.createElement("");
             this->toXML(doc, &pat,p, true);
             fac->appendChild(pat);
        }
    }
}
void SendMessageControl::toXMLEmptyFacility(QDomDocument& doc,QDomElement* fac, Facility* aFacility)
{

    fac->setTagName("Facility");
    fac->setAttribute("ID", aFacility->getFacilityId());
    fac->setAttribute("LTC", aFacility->getNumBeds(EOBC::LTC));
    fac->setAttribute("AC", aFacility->getNumBeds(EOBC::AC));
    fac->setAttribute("CCC", aFacility->getNumBeds(EOBC::CCC));
    fac->setAttribute("name", aFacility->getFacilityName());
    fac->setAttribute("coordinateX", aFacility->getLocation().x());
    fac->setAttribute("coordinateY", aFacility->getLocation().y());
}

/**
 * Makes an Area XML tag that contains a facility tag to be used in a message to add beds to a facility
 *
 * @param newAC the delta of AC beds to be put
 * @param aFacility the Facility the beds will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 *
 */
void SendMessageControl::toXML(QDomDocument& doc,QDomElement* area, Facility* aFacility, int deltaAC, int deltaCCC, int deltaLTC){
    QDomElement fac = doc.createElement("Facility");
    fac.setTagName("Facility");
    fac.setAttribute("ID", aFacility->getFacilityId());
    fac.setAttribute("LTC", deltaLTC);
    fac.setAttribute("AC", deltaAC);
    fac.setAttribute("CCC", deltaCCC);
    fac.setAttribute("name", aFacility->getFacilityName());
    area->setAttribute("ID", aFacility->getAreaThisIsIn()->getAreaId());
    area->appendChild(fac);
}
/**
 * Sends an Add message to add patients to a facility
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area the patients will be added to
 * @param aFacility the Facility the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 *
 */
void SendMessageControl::addPatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*>& p)
{
    this->doStuffToPatients("Add",  remote, anArea, aFacility, p);
}

/**
 * Sends an Add message to add patients to a waiting list
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area with the waiting list the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendMessageControl::addPatients(bool remote, Area* anArea, QLinkedList<Patient*>& p)
{
    /// @todo IMPLEMENT
}

/**
 * Sends a Delete message to delete patients from a Facility
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area with the Facility that the patients will be added to
 * @param aFacility the Facility the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendMessageControl::deletePatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*>& p)
{
   this->doStuffToPatients("Delete",  remote, anArea, aFacility, p);
}

/**
 * Sends a Delete message to delete patients from a waiting list
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area whose waiting list the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendMessageControl::deletePatients(bool remote, Area* anArea, QLinkedList<Patient*>& p)
{
   /// @todo IMPLEMENT
}

/**
 * Sends a Rebuild message containing all facility information
 *
 * @param anArea the Area the patients will be added to
 *
 * @param aFacility the Facility the patients will be added to
 *
 */
void SendMessageControl::rebuild(Area* anArea, Facility* aFacility){
    QDomDocument doc;
    QDomElement rebui = doc.createElement("Rebuild");
    QDomElement e = doc.createElement("Area");
    this->toXML(doc,&e, anArea, aFacility);
    rebui.appendChild(e);
    doc.appendChild(rebui);
   // doc.appendChild(e);
    QByteArray data = doc.toByteArray();
    qDebug(doc.toString().toAscii());
    sendQByte(data);
}
/**
 * Sends an empty Rebuild message
 *
 */
void SendMessageControl::rebuild(){
    QDomDocument doc;
    QDomElement e = doc.createElement("");
    e.setTagName("Rebuild");
    QByteArray data = doc.toByteArray();

    sendQByte(data);
}

/**
 * Private helper method, sends a message
 *
 * @param str the command that this message should execute e.g. 'Add', 'Delete'
 *
 * @param p the list of Patients that will be transformend into an XML tag
 *
 * @param anArea the Area the patients will be added to
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 *
 * @param aFacility the Facility the patients will be added to
 *
 */
void SendMessageControl::doStuffToPatients(QString str, bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p){
    QDomDocument doc;
    QDomElement el = doc.createElement("Area");
    this->toXML(doc,&el,  anArea, aFacility,  p);

    QDomElement tempE = doc.createElement(str);
    QDomElement* e = &tempE;
    e->setTagName(str);
    if(remote)
    {
        e->setAttribute("remote", "true");
    }else
    {
        e->setAttribute("remote", "false");
    }

    e->appendChild(el);
    /// @todo remove doc attributes
    doc.appendChild(*e);
    Logger::debugMessage("sendMessageControl", "doStuffToPatients", "OMG XML", doc.toString());
    qDebug(doc.toString().toAscii());
    QByteArray data = doc.toByteArray();
    sendQByte(data);
}

void SendMessageControl::sendQByte(QByteArray &data)
{
    _communication.sendMessage(data);
}

void SendMessageControl::addBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds){
    QDomDocument doc;
    QDomElement add = doc.createElement("Add");
    if(remote){
        add.setAttribute("remote", "true");
    }else{
        add.setAttribute("remote", "false");
    }
    QDomElement el = doc.createElement("Area");
    this->toXML(doc,&el, aFacility,deltaACBeds, deltaCCCBeds, deltaLTCBeds);
    add.appendChild(el);
    doc.appendChild(add);
    Logger::debugMessage("sendMessageControl", "addBeds", "OMG XML", doc.toString());
    QByteArray data = doc.toByteArray();
    qDebug(doc.toString().toAscii());
    sendQByte(data);
}
void SendMessageControl::addFacilities(bool remote,ID id, Facility* aFacility){
    QDomDocument doc;
    QDomElement add = doc.createElement("Add");
    if(remote){
        add.setAttribute("remote", "true");
    }else{
        add.setAttribute("remote", "false");
    }
    QDomElement are = doc.createElement("Area");
    are.setAttribute("ID", id);
    QDomElement el = doc.createElement("Facility");
    toXML(doc,&el, aFacility);
    are.appendChild(el);
    add.appendChild(are);
    doc.appendChild(add);
    Logger::debugMessage("sendMessageControl", "addFacil", "OMG XML", doc.toString());
    QByteArray data = doc.toByteArray();
    qDebug(doc.toString().toAscii());
    sendQByte(data);
}

void SendMessageControl::removeBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds){
    QDomDocument doc;
    QDomElement del = doc.createElement("Delete");

    if(remote){
        del.setAttribute("remote", "true");
    }else{
        del.setAttribute("remote", "false");
    }

    QDomElement el = doc.createElement("Area");
    this->toXML(doc,&el, aFacility,deltaACBeds, deltaCCCBeds, deltaLTCBeds);
    del.appendChild(el);
    doc.appendChild(del);
    Logger::debugMessage("sendMessageControl", "removeBeds", "OMG XML", doc.toString());
    QByteArray data = doc.toByteArray();
    sendQByte(data);
}

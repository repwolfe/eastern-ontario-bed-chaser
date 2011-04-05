#include "sendmessagecontrol.h"
/**
  * Empy contructor, code blows up without it... damn C++
  *
  */
SendMessageControl::SendMessageControl(){

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
void SendMessageControl::toXML(QDomElement* e,Patient* p, bool inpatient){
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

void SendMessageControl::toXML(QDomElement* e, Area* anArea, Facility* aFacility, QLinkedList<Patient*> pList){
    QDomElement* fac = new QDomElement();
    fac->setTagName("Facility");
    fac->setAttribute("ID", aFacility->getFacilityId());

    foreach(Patient* patInList, pList ){
        QDomElement* pat = new QDomElement();
        this->toXML(pat, patInList, true);
        fac->appendChild(*pat);
    }



    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());

    e->appendChild(*fac);
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
void SendMessageControl::toXML(QDomElement* e, Area* anArea, Facility* aFacility, Patient* p){
    QDomElement* fac = new QDomElement();
    fac->setTagName("Facility");
    fac->setAttribute("ID", aFacility->getFacilityId());
    QDomElement* pat = new QDomElement();
    this->toXML(pat, p, true);
    fac->appendChild(*pat);

    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());

    e->appendChild(*fac);

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
void SendMessageControl::toXML(QDomElement* e, Area* anArea, Facility* aFacility){
    QDomElement* fac = new QDomElement();
    this->toXML(fac, aFacility);
    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());
    e->appendChild(*fac);
}

/**
 * Helper function to the private methods, returns a complete view of a facility
 *
 * @param fac the element that Area will be returned in
 *
 * @param aFacility the Facility that will be turned into an XML tag
 *
 */
void SendMessageControl::toXML(QDomElement* fac, Facility* aFacility){

    fac->setTagName("Facility");
    fac->setAttribute("ID", aFacility->getFacilityId());
    fac->setAttribute("CCC", aFacility->getNumBeds(EOBC::LTC));
    fac->setAttribute("CCC", aFacility->getNumBeds(EOBC::AC));
    fac->setAttribute("CCC", aFacility->getNumBeds(EOBC::CCC));
    fac->setAttribute("name", aFacility->getFacilityName());
    fac->setAttribute("coordinateX", aFacility->getLocation().x());
    fac->setAttribute("coordinateY", aFacility->getLocation().y());

    PatientContainer * patients = aFacility->getPatientsForType(EOBC::LTC);
    if(patients->count() <= 0)
    {
        patients = aFacility->getPatientsForType(EOBC::AC);
        Patient* p;
        QDomElement* pat;
        foreach(QString str, patients->keys()){
             p = patients->find(str).value();
             pat = new QDomElement();
             this->toXML(pat,p, true);
             fac->appendChild(*pat);
        }

        patients = aFacility->getPatientsForType(EOBC::CCC);
        foreach(QString str, patients->keys()){
             p = patients->find(str).value();
             pat = new QDomElement();
             this->toXML(pat,p, true);
             fac->appendChild(*pat);
        }
    }else {
        Patient* p;
        QDomElement* pat;
        foreach(QString str, patients->keys()){
             p = patients->find(str).value();
             pat = new QDomElement();
             this->toXML(pat,p, true);
             fac->appendChild(*pat);
        }
    }
}
/**
 * Sends an Add message
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
void SendMessageControl::addPatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p){
    this->doStuffToPatients("Add",  remote, anArea, aFacility, p);
}

/**
 * Sends a Delete message
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
void SendMessageControl::deletePatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p){
   this->doStuffToPatients("Delete",  remote, anArea, aFacility, p);
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
    QDomElement* e = new QDomElement();
    this->toXML(e, anArea, aFacility);
    QByteArray data = e->toDocument().toByteArray();
    emit sendQByte(data);
}
/**
 * Sends an empty Rebuild message
 *
 */
void SendMessageControl::rebuild(){
    QDomElement* e = new QDomElement();
    e->setTagName("Rebuild");
    QByteArray data = e->toDocument().toByteArray();
    emit sendQByte(data);
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
    QDomElement* el = new QDomElement();
    this->toXML(el,  anArea, aFacility,  p);

    QDomElement* e = new QDomElement();
    e->setTagName(str);
    if(remote)
    {
        e->setAttribute("remote", "true");
    }else
    {
        e->setAttribute("remote", "false");
    }
    e->appendChild(*el);
    QByteArray data = e->toDocument().toByteArray();
    emit sendQByte(data);
}

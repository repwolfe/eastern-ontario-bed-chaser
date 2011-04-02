#include "sendmessagecontrol.h"

SendMessageControl::SendMessageControl()
{
}

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
};

void SendMessageControl::toXML(QDomElement* area, Area* anArea, Facility* aFacility, Patient* p){
    QDomElement* fac = new QDomElement();
    fac->setTagName("Facility");
    fac->setAttribute("ID", aFacility->getFacilityId());
    QDomElement* pat = new QDomElement();
    this->toXML(pat, p, true);
    fac->appendChild(*pat);

    area->setTagName("Area");
    area->setAttribute("ID", anArea->getAreaId());

    area->appendChild(*fac);

};
void SendMessageControl::toXML(QDomElement* e, Area* anArea, Facility* aFacility){
    QDomElement* fac = new QDomElement();
    this->toXML(fac, aFacility);
    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());
    e->appendChild(*fac);
}

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
    if(patients->count() <= 0){
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
};


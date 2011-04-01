#include "sendmessagecontrol.h"

SendMessageControl::SendMessageControl()
{
}
/*
QDomElement toXML(Patient* p){
    QDomElement* e = new QDomElement();
    e->setTagName("Patient");
    e->setAttribute("healthCardNumber", p->getHealthCardNumber());
    e->setAttribute("firstName", p->getFirstName());
    e->setAttribute("lastName", p->getLastName());
    e->setAttribute("reqCare", p->getRequiredCare());
    e->setAttribute("occCare", p->getOccupiedCare());
    return e*;
};

QDomElement toXML(Area* anArea, Facility* aFacility, Patient* p){
    QDomElement fac = new QDomElement();
    fac.setTagName("Facility");
    fac.setAttribute("ID", aFacility->getFacilityId());
    fac.appendChild(this->toXML(p));

    QDomElement area = new QDomElement();
    area.setTagName("Area");
    area.setAttribute("ID", anArea->getAreaId());

    area.appendChild(fac);

    return area;
};
*/

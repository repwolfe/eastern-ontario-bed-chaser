#include "storageHandler.h"
#include <QtXml/qdom.h>
#include "logger.h"
#include "convenience.h"
#include <QList>
/**
  * This constructor takes the name of a file to load the model
  * @param filename: The name of the file.
  *
  */
StorageHandler::StorageHandler(QString fileName)
{
    int error =  this->loadModel(fileName);
    switch(error){
    case -1: Logger::errorMessage("storageHandler", "loadModel","Could not open storage file");
        break;
    case -2: Logger::errorMessage("storageHandler", "loadModel","Failed on doc.setContent()");
        break;
    case -3: Logger::errorMessage("storageHandler", "loadModel","contents of file should start with <Area>");
        break;
    default: break;
    }
}

/**
  This is the Private empty constructor for StorageHandler
 */
StorageHandler StorageHandler::_StorageHandler()
{
    StorageHandler tmp(QString(""));
    return tmp;
}

/**
 * This loads the model from a file
 *
 * @param filename is the name of the file
 *
 * @return int > 0 if it worked, int < 0 otherwise
 */
int StorageHandler::loadModel(QString fileName){
    QDomDocument doc;
    if( fileName != ""){
        QFile file(fileName);
        //open the file
        if( !file.open(QIODevice::ReadOnly))
            return -1;
        QByteArray byte(file.readAll());
        if( !doc.setContent( byte, false) ) //load the file into doc
        {
            file.close();
            return -2;
        }
        file.close();
        //load the file into the QDomElement
        QDomElement root = doc.documentElement();

        if( root.tagName() != "Area" ){
            Logger::errorMessage("storageHandler", "loadModel","root is not an Area", QString(root.tagName()));
            return -3;
        }


        //parse the xml into objsects
        Area* anArea = new Area((root.attribute("ID").toInt()));
        _currentArea = anArea;

        QDomNode rootChild = root.firstChild();
        QDomNode n;
        QDomElement e;

        while( !rootChild.isNull() )
        {
            e = rootChild.toElement();
              Logger::infoMessage("storageHandler", "loadModel", "The rootChild Name= ", e.tagName());

            n = rootChild.firstChild();
            if(rootChild.nodeName() =="WaitingList")
                 this->parseWaitingList(anArea, &n);

            if(rootChild.nodeName() =="Facility"){
                e = rootChild.toElement();

                //set up facility
                QString ID = e.attribute("ID", "0");
                QString name = e.attribute("name", "noName");
                int LTC = e.attribute("LTC", "0").toInt();
                int CCC = e.attribute("CCC", "0").toInt();
                int AC = e.attribute("AC", "0").toInt();
                QPoint coordinates(e.attribute("coordinateX", "0").toInt(), e.attribute("coordinateY", "0").toInt());
                Facility* aFacility = new Facility(ID.toInt(),name,AC,CCC,LTC,coordinates);
                _currentFacility = aFacility;
                //set up facility

                this->parseFacility(aFacility, &n);
                anArea->addFacility(aFacility);
            }

            rootChild = rootChild.nextSibling();
        }

    }
    return 0;
}
/**
 * Helper function to loadModel
 *
 * @param anArea that will contain a waitingList with patients parsed in this step
 *
 * @param n is an xml node of the first patient in the waiting List
 *
 */
void StorageHandler::parseWaitingList(Area* anArea,QDomNode* n){
    QDomElement e;
    QDomNode node;
    while(!n->isNull())
    {
        e = n->toElement();

        QString healthCardNumber = e.attribute( "healthCardNumber", "1111111111" );
        QString firstName = e.attribute( "firstName", "FirstName" );
        QString lastName = e.attribute( "lastName", "LastName" );
        QDate dateAdded  = Convenience::fromXML(e.attribute("dateAdded", "2000-02-02"));
        Logger::infoMessage("storageHandler","parseWaitingList", "Patient added to waiting list name= ", firstName);
        anArea->addPatientToWaitingList(healthCardNumber, firstName, lastName, dateAdded);
        node = e.nextSibling();
        n = &(node);

    }

}
/**
 * Helper function to loadModel
 *
 * @param afacility that will contain patients parsed in this step
 *
 * @param n is an xml node of the first patient in the facility
 *
 */
void StorageHandler::parseFacility(Facility* aFacility, QDomNode* n){
    QDomElement e;
    QDomNode node;
    while( !n->isNull() )
    {
        e = n->toElement();

        QString healthCardNumber = e.attribute( "healthCardNumber", "1111111111" );
        QString firstName = e.attribute( "firstName", "noFirstName" );
        QString lastName = e.attribute( "lastName", "noLastName" );
        int reqCare = e.attribute("reqCare", "0").toInt();
        int occCare = e.attribute("occCare", "0").toInt();
        QDate dateAdmitted  = Convenience::fromXML(e.attribute("dateAdded", "2000-02-02"));
        Logger::infoMessage("storageHandler","parseWaitingList", "Patient added to a facility pName= ", firstName);

        Patient* p = new Patient(healthCardNumber, firstName, lastName,  Convenience::intToCareType(reqCare));
        p->setAdmissionDate(dateAdmitted);
        aFacility->addPatientToBed(p, Convenience::intToCareType(occCare));
        node = e.nextSibling();
        n = &(node);

    }

}

StorageHandler::~StorageHandler(){

}
/**
 * Helper function to saveModel the WaitingList in an XML format
 *
 * @param aWaitingList that will be transformend into XML tags
 *
 */
QDomElement* saveWaitingList(WaitingList* aWaitingList){
    QDomElement* e = new QDomElement();
    e->setTagName("WaitingList");
    QList<Patient*> pList = aWaitingList->values();
    foreach(Patient* p, pList){

        QDomElement* pat = new QDomElement();
        pat->setTagName("Patient");
        pat->setAttribute("healthCardNumber", p->getHealthCardNumber());
        pat->setAttribute("firstName", p->getFirstName());
        pat->setAttribute("lastName", p->getLastName());
        pat->setAttribute("reqCare", int(p->getRequiredCare()));
        pat->setAttribute("dateAdded", Convenience::toXML(p->getDatePlacedOnWaitingList()));
        e->appendChild(*pat);
    }
    return e;
}
/**
 * Helper function to saveModel the WaitingList in an XML format
 *
 * @param aFacility that will be transformend into XML tags
 *
 */
QDomElement* saveFacility(Facility* aFacility){
 QDomElement* e = new QDomElement();
 e->setTagName("Facility");
 aFacility->getFacilityId(); //to make robbie happy

 return e;
}

/**
 * Helper function to saveModel the WaitingList in an XML format
 *
 * @param aFacility that will be transformend into XML tags
 *
 */
QDomElement* saveArea(Area* anArea){
    QDomElement* e = new QDomElement();
    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());

    return e;
}
/// @todo fix save model
int StorageHandler::saveModel(QString fileName, Area* anArea, int facilityID){
    //QDomElement* wl;  //make robbie happy
    facilityID++; // make robbie happy
    if(anArea && !anArea->getWaitingList().isEmpty()){
       //wl = this->saveWaitingList(anArea);
    }
    QDomElement* e = new QDomElement();
    e->setTagName("Area");
    e->setAttribute("ID", anArea->getAreaId());
    //e->appendChild(QDomNode(wl*));
    QFile file(fileName);
    //open the file
    if( !file.open(QIODevice::WriteOnly))
        return -1;
    return 0;
}

Facility* StorageHandler::getFacility(ID areaID, ID facilityID){
  Area* anArea = this->_getArea(areaID);
  return anArea->getFacility(facilityID);
}

WaitingList StorageHandler::getWaitingList(ID areaID){
    Area* anArea = this->_areas.find(areaID).value();
    return anArea->getWaitingList();
}

PatientContainer* StorageHandler::getPatients(ID areaID, ID facilityID, EOBC::CareType reqCare){
    Area* anArea = this->_areas.find(areaID).value();
    return anArea->getFacility(facilityID)->getPatientsForType(reqCare);
}

/// @todo use robbie's new facility function that returns all patients
PatientContainer* StorageHandler::getPatients(ID areaID, ID facilityID){
    Area* anArea = this->_areas.find(areaID).value();
    return anArea->getFacility(facilityID)->getPatientsForType(EOBC::AC);//replace
}

areaList StorageHandler::getAreas(){
    return _areas;
}

Area* StorageHandler::_getArea(ID id){
    Area* anArea= this->getAreas().find(id).value();
    if(!anArea)
        anArea = new Area(id);
    this->getAreas().insert(id, anArea);
    return anArea;
}
void StorageHandler::addPatient(ID areaID, ID facilityID, Patient* p){
    Area* area = this->_areas.find(areaID).value();
    area->getFacility(facilityID)->addPatientToBed(p, p->getRequiredCare());
}

void StorageHandler::addPatient(ID areaID, Patient* p){
    Area* area = this->_areas.find(areaID).value();
    /// @todo add robbie's WaitingList.add(Patient* p)
}

void StorageHandler::deletePatient(ID areaID, ID facilityID, Patient* p){
    Area* area = this->_areas.find(areaID).value();
    area->getFacility(facilityID)->removePatient(p->getHealthCardNumber());
}

void StorageHandler::deletePatient(ID areaID, Patient* p){
     Area* area = this->_areas.find(areaID).value();
     area->removePatientFromWaitingList(p->getHealthCardNumber());
}

QMap<ID, Area*> StorageHandler::getModel(){
    QMap<ID, Area*> map;
    while(!this->_model.isEmpty())
    {
        Area* anArea = this->_model.takeFirst();
        map.insert(anArea->getAreaId(), anArea);
    }
    return map;
}

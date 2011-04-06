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
    _filename = fileName;
    /*
    int error;// =  this->loadModel(fileName);
    switch(error){
    case -1: Logger::errorMessage("storageHandler", "loadModel","Could not open storage file");
        break;
    case -2: Logger::errorMessage("storageHandler", "loadModel","Failed on doc.setContent()");
        break;
    case -3: Logger::errorMessage("storageHandler", "loadModel","contents of file should start with <Area>");
        break;
    default: break;
    }
    */
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
        anArea->makeThisOurArea();

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
		_areas.insert(anArea->getAreaId(), anArea);
		if (anArea->addFacility(aFacility))
		{
		    emit facilityAdded(anArea->getAreaId(),aFacility,false);
		}
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

QMap<ID, QString> StorageHandler::getFacilityNames()
{
    QMap<ID, QString> map;
    foreach (Area* area, _areas)
    {
	FacilityList& facilities = area->getFacilities();
	foreach (Facility* fac, facilities)
	{
	    map[fac->getFacilityId()] = fac->getFacilityName();
	}
    }
    return map;
}

QMap<ID, Facility*> StorageHandler::getFacilityPointers()
{
    QMap<ID, Facility*> map;
    foreach (Area* area, _areas)
    {
	FacilityList& facilities = area->getFacilities();
	foreach (Facility* fac, facilities)
	{
	    map[fac->getFacilityId()] = fac;
	}
    }
    return map;
}

QMap<ID, Area*> StorageHandler::getAllAreas()
{
    QMap<ID, Area*> map;
    foreach (Area* area, _areas)
    {
	map[area->getAreaId()] = area;
    }
    return map;
}

QMap<ID, QLinkedList<Patient*> > StorageHandler::getAllPatients()
{
    QMap<ID, QLinkedList<Patient*> > map;
    foreach (Area* area, _areas)
    {
	FacilityList& facs = area->getFacilities();
	foreach (Facility* fac, facs)
	{
	    map[fac->getFacilityId()] = fac->getAllPatientsList();
	}
    }
    return map;
}

QMap<ID, QLinkedList<Patient*> > StorageHandler::getAllAreasWaitingList()
{
    QMap<ID, QLinkedList<Patient*> > map;
    foreach (Area* area, _areas)
    {
	map[area->getAreaId()] = area->getWaitingListAsList();
    }
    return map;
}

/// @todo reuse code to avoid duplication
QMap<ID, QVector<int> > StorageHandler::getTotalBeds() //AC, CCC, LT
{
    QMap<ID, QVector<int> > map;
    foreach (Area* area, _areas)
    {
	FacilityList& facs = area->getFacilities();
	foreach (Facility* fac, facs)
	{
	    QVector<int> beds(3);
	    beds[0] = fac->getNumBeds(EOBC::AC);
	    beds[1] = fac->getNumBeds(EOBC::CCC);
	    beds[2] = fac->getNumBeds(EOBC::LTC);
	    map[fac->getFacilityId()] = beds;
	}
    }
    return map;
}

/// @todo reuse code to avoid duplication
QMap<ID, QVector<int> > StorageHandler::getOccupiedBeds()
{
    QMap<ID, QVector<int> > map;
    foreach (Area* area, _areas)
    {
	FacilityList& facs = area->getFacilities();
	foreach (Facility* fac, facs)
	{
	    QVector<int> beds(3);
	    beds[0] = fac->getNumBedsOccupied(EOBC::AC);
	    beds[1] = fac->getNumBedsOccupied(EOBC::CCC);
	    beds[2] = fac->getNumBedsOccupied(EOBC::LTC);
	    map[fac->getFacilityId()] = beds;
	}
    }
    return map;
}

/**
 * @return Facility with ID or NULL
 */
Facility* StorageHandler::getFacility(ID facID)
{
    Facility* fac = 0;
    foreach (Area* area, _areas)
    {
	FacilityList& facs = area->getFacilities();
	FacilityList::const_iterator iter = facs.find(facID);
	if (iter != facs.end())
	{
	    fac = iter.value();
	    break;
	}
    }
    return fac;
}

/*
WaitingList StorageHandler::getWaitingList(ID areaID){
    Area* anArea = this->_areas.find(areaID).value();
    return anArea->getWaitingList();
}

PatientContainer* StorageHandler::getPatients(ID areaID, ID facilityID, EOBC::CareType reqCare){
    Area* anArea = this->_areas.find(areaID).value();
    return anArea->getFacility(facilityID)->getPatientsForType(reqCare);
}

/// @todo use robbie's new facility function that returns all patients
PatientContainer* StorageHandler::getPatients(ID areaID, ID facilityID)
{
    Area* anArea = this->_areas.find(areaID).value();
    return anArea->getFacility(facilityID)->getPatientsForType(EOBC::AC);//replace
}
*/

areaList StorageHandler::getAreas(){
    return _areas;
}

Area* StorageHandler::_getArea(ID id){
    areaList::iterator area = _areas.find(id);
    Area* anArea = 0;
    if (area == _areas.end())
    {
        anArea = new Area(id);
        _areas.insert(id, anArea);
    }
    else { anArea = area.value(); }
    return anArea;
}
void StorageHandler::addPatient(ID areaID, ID facilityID, Patient* p){
    areaList::iterator area = _areas.find(areaID);
    if (area != _areas.end())
    {
        area.value()->getFacility(facilityID)->addPatientToBed(p, p->getRequiredCare());
    }

}
void StorageHandler::addFacility(ID areaID, Facility* f,bool remote){
    Area* area = _getArea(areaID);
    if (area->addFacility(f))
    {
        emit this->facilityAdded(areaID,f,remote);
    }
    // Facility already in Area, delete
    else
    {
        //delete f;
    }

}

void StorageHandler::addPatient(ID areaID, Patient* p){
    Area* area = _getArea(areaID);
    area->addPatientToWaitingList(p);
}

void StorageHandler::deletePatient(ID areaID, ID facilityID, Patient* p){
    Area* area = _getArea(areaID);
    area->getFacility(facilityID)->removePatient(p->getHealthCardNumber());
}

void StorageHandler::deletePatient(ID areaID, Patient* p){
     Area* area = _getArea(areaID);
     area->removePatientFromWaitingList(p->getHealthCardNumber());
}

Facility* StorageHandler::getCurrentFacility()
{
    return this->_currentFacility;
}

Area* StorageHandler::getCurrentArea()
{
    return this->_currentArea;
}
QString StorageHandler::getFileName()
{
    return _filename;
}

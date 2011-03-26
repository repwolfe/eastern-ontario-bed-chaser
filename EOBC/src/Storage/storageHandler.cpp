#include "storageHandler.h"
#include <QtXml/qdom.h>
#include "logger.h"
#include "qmessagebox.h"

/**
  * This constructor takes the name of a file to load the model
  * @param filename: The name of the file.
  *
  * @todo implement a default constructor
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
};

/**
 * This loads the model from a file
 *
 * @param filename is the name of the file
 *
 * @return > 0 if it worked, < 0 otherwise
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

        QDomNode rootChild = root.firstChild();
        QDomNode n;
        QDomElement* e;

        while( !rootChild.isNull() )
        {
            e = &(rootChild.toElement());
              Logger::infoMessage("storageHandler", "loadModel", "The rootChild Name= ", e->tagName());

            n = rootChild.firstChild();
            if(rootChild.nodeName() =="WaitingList")
                 this->parseWaitingList(anArea, &n);

            if(rootChild.nodeName() =="Facility"){
                e = &(rootChild.toElement());
                QString ID = e->attribute("ID", "0");
                QString name = e->attribute("name", "noName");
                QString LTC = e->attribute("LTC", "0");
                QString CCC = e->attribute("CCC", "0");
                QString AC = e->attribute("AC", "0");
                QPoint coordinates(e->attribute("coordinateX", "0").toInt(), e->attribute("coordinateY", "0").toInt());
                Facility* aFacility = new Facility(ID.toInt(),name,AC.toInt(),CCC.toInt(),coordinates);
                aFacility->addBeds(LTC.toInt(),EOBC::LTC);
                anArea->addFacility(aFacility);
                this->parseFacility(aFacility, &n);
            }

            rootChild = rootChild.nextSibling();
        }

    }
    return 0;
};

void StorageHandler::parseWaitingList(Area* anArea,QDomNode* n){
    QDomElement* e;
    while( !n->isNull() )
    {
        e = &(n->toElement());

        QString healthCardNumber = e->attribute( "healthCardNumber", "1111111111" );
        QString firstName = e->attribute( "firstName", "FirstName" );
        QString lastName = e->attribute( "lastName", "LastName" );
        QDate dateAdded(12,12,12);
        Logger::infoMessage("storageHandler","parseWaitingList", "Patient added to waiting list name= ", firstName);
        anArea->addPatientToWaitingList(healthCardNumber, firstName, lastName, dateAdded);
        n = &(e->nextSibling());

    }
    /**
        QStringList dateList = e->attribute("dateAdded").split("-");
        /// @todo parse the date properly
       // QString(dateList.at(0)).toInt();
      //  QString(dateList.at(1)).toInt();
      //  QString(dateList.at(2)).toInt();
      //  QDate dateAdded(dateList.at(0));
        QDate dateAdded(12,12,12);
       /// @todo QRegExp exp() in date parsing
//YYYY-MM-DDThh:mm:ss
    */
};

void StorageHandler::parseFacility(Facility* aFacility, QDomNode* n){
    QDomElement* e;
    while( !n->isNull() )
    {
        e = &(n->toElement());

        QString healthCardNumber = e->attribute( "healthCardNumber", "1111111111" );
        QString firstName = e->attribute( "firstName", "noFirstName" );
        QString lastName = e->attribute( "lastName", "noLastName" );
        int reqCare = e->attribute("reqCare", "0").toInt();
        int occCare = e->attribute("occCare", "0").toInt();
        QDate dateAdded(12,12,12);
        QDate dateAdmitted(1984,11,11);
        Logger::infoMessage("storageHandler","parseWaitingList", "Patient added to a facility pName= ", firstName);
        Patient* p = new Patient(healthCardNumber, firstName, lastName, static_cast<EOBC::CareType>(reqCare));
        aFacility->addPatientToBed(p,static_cast<EOBC::CareType>(occCare));
        n = &(e->nextSibling());

    }
    /**
        QStringList dateList = e->attribute("dateAdded").split("-");
        /// @todo parse the date properly
       // QString(dateList.at(0)).toInt();
      //  QString(dateList.at(1)).toInt();
      //  QString(dateList.at(2)).toInt();
      //  QDate dateAdded(dateList.at(0));
        QDate dateAdded(12,12,12);
       /// @todo QRegExp exp() in date parsing
//YYYY-MM-DDThh:mm:ss
    */
};

StorageHandler::~StorageHandler(){

}

int StorageHandler::saveModel(QString fileName, Area* anArea, int facilityID){
    fileName.begin();//delete me
    anArea->setAreaId(facilityID);//delete me
    return 0;
};

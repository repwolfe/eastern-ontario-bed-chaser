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
    this->loadModel(fileName);
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
    Logger::infoMessage("storageHandler", "loadModel"," fileName IS=", fileName);
    //open the file
    QString* errorMsg(&fileName);
    if( !file.open(QIODevice::ReadOnly))
      return -1;
    QByteArray byte(file.readAll());
    if( !doc.setContent( byte, false) ) //load the file into doc
    {
      Logger::errorMessage("storageHandler", "loadModel","Failed on setContent()", *errorMsg);
      file.close();
      return -2;
    }
    Logger::infoMessage("storageHandler", "loadModel","doc.setContent suceeded");
    file.close();
    //load the file into the QDomElement
    QDomElement root = doc.documentElement();
    if( root.tagName() != "Area" )
      return -3;

    Logger::errorMessage("storageHandler", "loadModel","root is not an Area", QString(root.tagName()));

    //parse the xml into objsects
    QDomNode n = root.firstChild();

            /** /// @todo change the parsing of this into a complex series of
                --if-- statements, or a switch
                */
    QDomElement e;
    while( !n.isNull() )
    {
      e = n.toElement();
      if( !e.isNull() )
      {
        if( e.tagName() == "WaitingList" )
        {
                //parse the waiting list
            while( !e.isNull() && (e.tagName() == "WaitingList" || e.tagName() == "Patient") )
            {
                Patient* p = new Patient(e.attribute( "healthCardNumber", "1111111111" ),e.attribute( "firstName", "FirstName" ), e.attribute( "lastName", "LastName" ),EOBC::LTC);
                //create patients on a waiting list
                QMessageBox::information( 0, "Patient", p->getName() +"\n" + p->getHealthCardNumber() + "\n");
                n = n.nextSibling();
                e = n.toElement();
            }
        }


        }
      n = n.nextSibling();
      }

}
    return 0;
};

StorageHandler::~StorageHandler(){

}

int StorageHandler::saveModel(QString fileName, Area* anArea, int facilityID){
    fileName.begin();//delete me
    anArea->setAreaId(facilityID);//delete me
return 0;
};

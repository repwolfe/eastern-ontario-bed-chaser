#include "ReceiveMessageControl.h"

ReceiveMessageControl::ReceiveMessageControl(CommunicationReceiveInterface &receiveData)
{
    connect(&receiveData, SIGNAL(processTheMessage(QByteArray&)), SLOT(_parseMessage(QByteArray&)));
}

/**
 * Used to parse all incoming messages
 *
 * @param qByte the byte received from another Facility
 *
 */
void ReceiveMessageControl::_parseMessage(QByteArray& qByte){
    QDomDocument doc;
    doc.setContent(qByte);
     QDomNode n = doc.firstChild();
     QDomElement e = n.toElement();
    if(e.tagName() == "Add")
    {
        parseAdd(e);
    }else if (e.tagName() == "Delete")
    {
        parseDelete(e);
    }else if (e.tagName() == "Rebuild")
    {
        parseRebuild(e);
    }
}

/**
 * Helper function to parseMessage parses messages in the Add tag
 *
 * @param addTag the XML tag titled 'Add'
 *
 */
void ReceiveMessageControl::parseAdd(QDomElement addTag){
    this->parseAddDeleteRebuild(addTag,true, false);
}

/**
 * Helper function to parseMessage parses messages in the Delete tag
 *
 * @param deleteTag the XML tag titled 'Delete'
 *
 */
void ReceiveMessageControl::parseDelete(QDomElement deleteTag){
    this->parseAddDeleteRebuild(deleteTag,false, false);
}

/**
 * Helper function to parseMessage parses messages in the Delete tag
 *
 * @param rebuildTag the XML tag titled 'Rebuild'
 *
 */
void ReceiveMessageControl::parseRebuild(QDomElement rebuildTag){
    this->parseAddDeleteRebuild(rebuildTag,true, true);
    //rebuildTag, (Add everything in rebuild?), Rebuild?
}

/**
 * Helper function to parse(add/delete)  parses messages in the Add/Delete tag
 *
 * @param tag the XML tag titled 'Add' or 'Delete'
 *
 * @param add if the tag isan add tag this is true else it is false Rebuild defaults to false
 */
void ReceiveMessageControl::parseAddDeleteRebuild(QDomElement tag, bool add, bool rebuild){

 bool remote = false;
 if(tag.attribute("remote", "false") == "true")
     remote = true;
 int areaID, facilityID;
 QDomNode n(tag);
 QDomElement e = tag.childNodes().at(0).toElement();
 Patient* p;
 while(!e.isNull()){

     if(e.tagName() == "Area"){
         areaID = e.attribute("ID", "0").toInt();
         e = e.childNodes().at(0).toElement();
     }
     if(e.tagName() == "Facility"){
         facilityID = e.attribute("ID", "0").toInt();
         QString name = e.attribute("name", "noName");
         int LTC = e.attribute("LTC", "0").toInt();
         int CCC = e.attribute("CCC", "0").toInt();
         int AC = e.attribute("AC", "0").toInt();
         QPoint coordinates(e.attribute("coordinateX", "0").toInt(), e.attribute("coordinateY", "0").toInt());

         e = e.childNodes().at(0).toElement();
         if(add)
         {
             Facility f(facilityID,name,AC,CCC,LTC,coordinates);
             emit addFacility(areaID,&f);
             emit addBeds(areaID, facilityID, EOBC::LTC, LTC);
             emit addBeds(areaID, facilityID, EOBC::AC, AC);
             emit addBeds(areaID, facilityID, EOBC::CCC, CCC);

        }else
         {
            emit removeBeds(areaID, facilityID, EOBC::LTC, LTC);
            emit removeBeds(areaID, facilityID, EOBC::AC, AC);
            emit removeBeds(areaID, facilityID, EOBC::CCC, CCC);
        }
         if(rebuild)
           emit sendRebuild(areaID, facilityID);

     }
     if(e.tagName() == "Patient"){

             QString healthCardNumber = e.attribute( "healthCardNumber", "1111111111" );
             QString firstName = e.attribute( "firstName", "FirstName" );
             QString lastName = e.attribute( "lastName", "LastName" );
             EOBC::CareType reqCare = Convenience::intToCareType( e.attribute("reqCare", "1").toInt());
             EOBC::CareType occCare = Convenience::intToCareType( e.attribute("occCare", "1").toInt());
             //parse date
                 QString date = e.attribute("dateAdmitted");
                 int year = date.section("-",0,0).toInt();
                 int month = date.section("-",1,1).toInt();
                 QString sDay = date.section("-",2,2);
                 sDay.truncate(2);
                 int day = sDay.toInt();
                 //remove the time from the date
                 QDate dateAdmitted(year, month, day);
                 p = new Patient(healthCardNumber, firstName, lastName, reqCare, occCare, dateAdmitted);
                 e = e.nextSiblingElement();
                 if(add)
                 {
                       emit addPatient(areaID, facilityID, p);
                    }else
                 {
                        emit deletePatient(areaID, facilityID, p);
                    }
     }
 }


}


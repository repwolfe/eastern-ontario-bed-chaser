#include "ReceiveMessageControl.h"

/**
 * Used to parse all incoming messages
 *
 * @param qByte the byte received from another Facility
 *
 */
void ReceiveMessageControl::parseMessage(QByteArray qByte){
    QDomElement e;
    QString str(qByte);
    e.setNodeValue(str);
    if(e.tagName() == "Add")
        parseAdd(e);
}

/**
 * Helper function to parseMessage parses messages in the Add tag
 *
 * @param addTag the XML tag titled 'Add'
 *
 */
void ReceiveMessageControl::parseAdd(QDomElement addTag){
    this->parseAddDelete(addTag,true);
}

/**
 * Helper function to parseMessage parses messages in the Delete tag
 *
 * @param addTag the XML tag titled 'Delete'
 *
 */
void ReceiveMessageControl::parseDelete(QDomElement deleteTag){
    this->parseAddDelete(deleteTag,false);
}
/**
 * Helper function to parse(add/delete)  parses messages in the Add/Delete tag
 *
 * @param tag the XML tag titled 'Add' or 'Delete'
 *
 * @param add if the tag isan add tag this is true else it is false
 */
void ReceiveMessageControl::parseAddDelete(QDomElement tag, bool add){
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
         emit addBeds(EOBC::LTC, LTC);
         emit addBeds(EOBC::AC, AC);
         emit addBeds(EOBC::CCC, CCC);

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


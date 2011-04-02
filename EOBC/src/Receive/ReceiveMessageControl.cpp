#include "ReceiveMessageControl.h"

void ReceiveMessageControl::parseMessage(QByteArray qByte){
    QDomElement e;
    QString str(qByte);
    e.setNodeValue(str);
    if(e.tagName() == "Add")
        parseAdd(e);
}

void ReceiveMessageControl::parseAdd(QDomElement addTag){
 bool remote = false;
 if(addTag.attribute("remote", "false") == "true")
     remote = true;
 int areaID, facilityID;
 QDomNode n(addTag);
 QDomElement e = addTag.childNodes().at(0).toElement();
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
     }
 }


}

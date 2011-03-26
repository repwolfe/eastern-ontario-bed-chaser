#ifndef STORAGEHANDLER_H
#define STORAGEHANDLER_H

#include "area.h"
#include "QFile"
#include "QLinkedList"
#include <QtXml/qdom.h>
#include "../Common/logger.h"
#include "qmessagebox.h"

/**
 * StorageHandler has a collection of Areas and uses an xml file
 * for persistant storage
 *
 * This class is part of the Storage subsystem described in D2.
 */
class StorageHandler
{
public:
    StorageHandler(QString fileName);
    virtual ~StorageHandler();
    int loadModel(QString fileName);
    int saveModel(QString filename, Area* anArea, int facilityID);
private:
   StorageHandler _StorageHandler();
   QLinkedList<Area*> _model;
   void parseWaitingList(Area* anArea,QDomNode* n);
   void parseFacility(Facility* aFacility,QDomNode* n);

};

#endif // STORAGEHANDLER_H

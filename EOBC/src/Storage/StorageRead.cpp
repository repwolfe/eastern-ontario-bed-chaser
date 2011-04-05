#include "StorageRead.h"

 QMap<ID, QString> StorageRead::getAllAreas(){
    QMap<ID, QString> areaNames;
    QMap<ID, Area*> model = this->_storageHandler->getModel();
    foreach(ID anID, model.keys()){
        areaNames.insert(anID,Convenience::areaIDtoQString(anID));
    }

   return areaNames;
}

void StorageRead::setStorageHandler(StorageHandler* aStorageHandler){
    this->_storageHandler = aStorageHandler;
}


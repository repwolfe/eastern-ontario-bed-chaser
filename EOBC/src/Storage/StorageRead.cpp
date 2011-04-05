#include "StorageRead.h"

 QMap<ID, Area*> StorageRead::getAllAreas(){
    return _storageHandler->getModel();
}

void StorageRead::setStorageHandler(StorageHandler* aStorageHandler){
    this->_storageHandler = aStorageHandler;
}


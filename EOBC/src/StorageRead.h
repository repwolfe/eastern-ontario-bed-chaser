#ifndef STORAGEREAD_H
#define STORAGEREAD_H

#include "storageHandler.h"
#include "convenience.h"
/**
 * @brief Interface that handles getting information
 *
 * This class is part of the Storage subsystem described in D2.
 */
class StorageRead : public QObject
{
    Q_OBJECT
public:
    StorageRead();
    QMap<ID, QString> getAllFacilityNames();
    QMap<ID, Facility*> getAllFacilities();
    QMap<ID, Area*> getAllAreas();
    QMap<ID, QLinkedList<Patient*> > getAllPatients();
    QMap<ID, QLinkedList<Patient*> > areasWaitingList;
    QMap<ID, QVector<int> > totalBeds; //AC, CCC, LTC
    QMap<ID, QVector<int> > occupiedBeds;
    Facility getFacility(ID facID);

    void setStorageHandler(StorageHandler* aStorageHandler);
    //report Data

private:
    StorageHandler* _storageHandler;
};

#endif // STORAGEREAD_H

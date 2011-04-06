#ifndef STORAGEREAD_H
#define STORAGEREAD_H
#include "area.h"
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
    StorageRead(StorageHandler* handle);
    QMap<ID, QString> getAllFacilityNames();
    QMap<ID, Facility*> getAllFacilityPointers();
    QMap<ID, Area*> getAllAreas();
    QMap<ID, QLinkedList<Patient*> > getAllPatients();
    QMap<ID, QLinkedList<Patient*> > getAllAreasWaitingList();
    QMap<ID, QVector<int> > getTotalBeds(); //AC, CCC, LTC
    QMap<ID, QVector<int> > getOccupiedBeds();
    Facility* getFacility(ID facID);
    Facility* getCurrentFacility();

    //report Data
private slots:
       void _addFacility(ID sourceArea, Facility* f);
signals:
        void addFacility(Facility* f);
private:
    StorageHandler* _storageHandler;
};

#endif // STORAGEREAD_H

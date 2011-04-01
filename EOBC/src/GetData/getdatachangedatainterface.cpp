#include "getdatachangedatainterface.h"

GetDataChangeDataInterface::GetDataChangeDataInterface(GetDataControl &getData) :
    _getData(getData)
{
    connect(&_getData, SIGNAL(receivedAllFacilities(QMap<ID,QString>)),
            SLOT(_receivedAllFacilities(QMap<ID,QString>)));
    connect(&_getData, SIGNAL(receivedAreasWaitingList(QMap<ID,QLinkedList<Patient*> >)),
            SLOT(_receivedAreasWaitingList(QMap<ID,QLinkedList<Patient*> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesPatients(QMap<ID,QLinkedList<Patient*> >)),
            SLOT(_receivedFacilitiesPatients(QMap<ID,QLinkedList<Patient*> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesCurrentBedNumbers(QMap<ID,QVector<int> >)),
            SLOT(_receivedFacilitiesCurrentBedNumbers(QMap<ID,QVector<int> >)));
    connect(&_getData, SIGNAL(receivedFacilitiesMinimumBedNumbers(QMap<ID,QVector<int> >)),
            SLOT(_receivedFacilitiesMinimumBedNumbers(QMap<ID,QVector<int> >)));
}

void GetDataChangeDataInterface::requestAllFacilities()
{
    _getData.requestAllFacilities();
}

void GetDataChangeDataInterface::requestFacilitiesPatients()
{
    _getData.requestFacilitiesPatients();
}

void GetDataChangeDataInterface::requestAreasWaitingList()
{
    _getData.requestAreasWaitingList();
}

void GetDataChangeDataInterface::requestFacilitiesCurrentBedNumbers()
{
    _getData.requestFacilitiesCurrentBedNumbers();
}

void GetDataChangeDataInterface::requestFacilitiesMinimumBedNumbers()
{
    _getData.requestFacilitiesMinimumBedNumbers();
}

void GetDataChangeDataInterface::_receivedAllFacilities(const QMap<ID, QString> &data)
{
    emit receivedAllFacilities(data);
}

void GetDataChangeDataInterface::_receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedFacilitiesPatients(data);
}

void GetDataChangeDataInterface::_receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient *> > &data)
{
    emit receivedAreasWaitingList(data);
}

void GetDataChangeDataInterface::_receivedFacilitiesCurrentBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesCurrentBedNumbers(data);
}

void GetDataChangeDataInterface::_receivedFacilitiesMinimumBedNumbers(const QMap<ID, QVector<int> > &data)
{
    emit receivedFacilitiesMinimumBedNumbers(data);
}

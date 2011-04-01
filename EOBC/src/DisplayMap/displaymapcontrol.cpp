#include "displaymapcontrol.h"

DisplayMapControl::DisplayMapControl(GetDataDisplayMapInterface& inter,QObject* parent) : QObject(parent)
{
    map = new Map();
    //map->setGeometry(QRect(90,0,1000,600));
    connectSlots(inter);
    for(int i=0;i<9;i++)
    {
        Facility* c = new Facility(1234,"Johnson Hospital",rand()%34,rand()%21,0,QPoint(200+rand()%800,350+rand()%100));
        CareType ct = Convenience::intToCareType(rand()%2+1);
        c->addPatientToBed(new Patient("111-111-111","fdsaf","Fdsaf",ct),ct);
        this->addFacility(c);
    }
    for(int i=0;i<9;i++)
    {
        Facility* c = new Facility(1234,"Johnson Hospital",0,0,rand()%40,QPoint(200+rand()%800,350+rand()%100));
        c->addPatientToBed(new Patient("111-111-111","fdsaf","Fdsaf",Convenience::intToCareType(0)),Convenience::intToCareType(0));
        this->addFacility(c);
    }
}
DisplayMapControl::~DisplayMapControl()
{
    delete map;
}

void DisplayMapControl::run()
{
    map->startTimer();
}
void DisplayMapControl::getLoggedOn(int permissions)
{
    map->setPermissions(permissions);
    run();
    map->show();
}
void DisplayMapControl::pressedAddBedsSlot(){emit pressedAddBeds();}
void DisplayMapControl::pressedAddFacilitiesSlot(){emit pressedAddFacilities();}
void DisplayMapControl::pressedAddUserAcctsSlot(){emit pressedAddUserAccts();}
void DisplayMapControl::pressedMovePatientsSlot(){emit pressedMovePatients();}
void DisplayMapControl::pressedAddPatientsSlot(){emit pressedAddPatients();}
void DisplayMapControl::pressedGenerateReportSlot(){emit pressedGenerateReport();}
void DisplayMapControl::pressedViewAllReportsSlot(){emit pressedViewAllReports();}
void DisplayMapControl::pressedUpdateWaitingListSlot(){emit pressedUpdateWaitingList();}
//
///GetDataSlots
//
void DisplayMapControl::addFacility(Facility* f)
{

    map->loadIcon(f);
}
void DisplayMapControl::addWaitingList(ID,QLinkedList<Patient*>&)
{

}
//
///GetDataSlots
//

void DisplayMapControl::connectSlots(GetDataDisplayMapInterface& inter)
{
    connect(map,SIGNAL(pressedAddBeds()),this,SLOT(pressedAddBedsSlot()));
    connect(map,SIGNAL(pressedAddFacilities()),this,SLOT(pressedAddFacilitiesSlot()));
    connect(map,SIGNAL(pressedAddUserAccts()),this,SLOT(pressedAddUserAcctsSlot()));
    connect(map,SIGNAL(pressedAddPatients()),this,SLOT(pressedAddPatientsSlot()));
    connect(map,SIGNAL(pressedMovePatients()),this,SLOT(pressedMovePatientsSlot()));
    connect(map,SIGNAL(pressedGenerateReport()),this,SLOT(pressedGenerateReportSlot()));
    connect(map,SIGNAL(pressedViewAllReports()),this,SLOT(pressedViewAllReportsSlot()));
    connect(map,SIGNAL(pressedUpdateWaitingList()),this,SLOT(pressedUpdateWaitingListSlot()));
    //
    ///GetDataSlots
    //

    connect(&inter,SIGNAL(receivedUpdatedFacility(Facility*)),this,SLOT(addFacility(Facility*)));
    connect(&inter,SIGNAL(receivedUpdatedWaitingList(ID,QLinkedList<Patient*>&)),this,SLOT(addWaitingList(ID,QLinkedList<Patient*>&)));
}


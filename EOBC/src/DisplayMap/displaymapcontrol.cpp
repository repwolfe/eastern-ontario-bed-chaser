#include "displaymapcontrol.h"
/** @todo remove testing
  *
  */
DisplayMapControl::DisplayMapControl(GetDataDisplayMapInterface& inter,QObject* parent) : QObject(parent)
{
    map = new Map();
    //map->setGeometry(QRect(90,0,1000,600));
    connectSlots(inter);

    //
    ///FOR TESTING ONLY, REMOVE
    //
    for(int i=0;i<9;i++)
    {
        Area * a = new Area(i);

        Facility* c = new Facility(1234,"Johnson Hospital"+QString::number(i),34,21,0,QPoint(200+rand()%800,350+rand()%100));
        a->addFacility(c);
        for(int i=0;i<40;i++)
        {
            CareType ct = Convenience::intToCareType(rand()%2);
            c->addPatientToBed(new Patient("111-111-11"+QString::number(i),"fdsaf","Fdsaf",ct),ct);
        }
        this->addFacility(c);
        delete a;
    }
    for(int i=0;i<9;i++)
    {
        Area * a = new Area(i);
        Facility* c = new Facility(1234,"Johnson Hospital"+QString::number(i+9),0,0,rand()%40,QPoint(200+rand()%800,350+rand()%100));
        a->addFacility(c);
        for(int i=0;i<10;i++)
            c->addPatientToBed(new Patient("111-111-11"+QString::number(i),"fdsaf","Fdsaf",Convenience::intToCareType(EOBC::LTC)),Convenience::intToCareType(2));
        this->addFacility(c);
        delete a;
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
void DisplayMapControl::addWaitingList(ID id,WaitingList& patients)
{
    map->setWaitingList(id,patients.count());
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
    connect(&inter,SIGNAL(receivedUpdatedWaitingList(ID,WaitingList&)),this,SLOT(addWaitingList(ID,WaitingList&)));
}


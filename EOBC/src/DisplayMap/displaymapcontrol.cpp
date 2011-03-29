#include "displaymapcontrol.h"

DisplayMapControl::DisplayMapControl(QObject* parent) : QObject(parent)
{
    map = new Map();
    //map->setGeometry(QRect(90,0,1000,600));
    connectSlots();
}
DisplayMapControl::~DisplayMapControl()
{
    delete map;
}

void DisplayMapControl::run()
{
    map->show();
}
void DisplayMapControl::getLoggedOn(int permissions)
{
    map->setPermissions(permissions);
}
void DisplayMapControl::pressedAddBedsSlot(){emit pressedAddBeds();}
void DisplayMapControl::pressedAddFacilitiesSlot(){emit pressedAddFacilities();}
void DisplayMapControl::pressedAddUserAcctsSlot(){emit pressedAddUserAccts();}
void DisplayMapControl::pressedMovePatientsSlot(){emit pressedMovePatients();}
void DisplayMapControl::pressedAddPatientsSlot(){emit pressedAddPatients();}
void DisplayMapControl::pressedGenerateReportSlot(){emit pressedGenerateReport();}
void DisplayMapControl::pressedViewAllReportsSlot(){emit pressedViewAllReports();}
void DisplayMapControl::connectSlots()
{
    connect(map,SIGNAL(pressedAddBeds()),this,SLOT(pressedAddBedsSlot()));
    connect(map,SIGNAL(pressedAddFacilities()),this,SLOT(pressedAddFacilitiesSlot()));
    connect(map,SIGNAL(pressedAddUserAccts()),this,SLOT(pressedAddUserAcctsSlot()));
    connect(map,SIGNAL(pressedAddPatients()),this,SLOT(pressedAddPatientsSlot()));
    connect(map,SIGNAL(pressedMovePatients()),this,SLOT(pressedMovePatientsSlot()));
    connect(map,SIGNAL(pressedGenerateReport()),this,SLOT(pressedGenerateReportSlot()));
    connect(map,SIGNAL(pressedViewAllReports()),this,SLOT(pressedViewAllReportsSlot()));
}


#ifndef DISPLAYMAPCONTROL_H
#define DISPLAYMAPCONTROL_H

#include "map.h"
#include "getdatadisplaymapinterface.h"
#include "facility.h"

class DisplayMapControl : public QObject
{
Q_OBJECT
public slots:
    void getLoggedOn(int);
    void pressedAddBedsSlot();
    void pressedAddFacilitiesSlot();
    void pressedAddUserAcctsSlot();
    void pressedMovePatientsSlot();
    void pressedAddPatientsSlot();
    void pressedGenerateReportSlot();
    void pressedViewAllReportsSlot();
    void pressedUpdateWaitingListSlot();
    ///
    ////GetDataSlots
    //
    void addFacility(Facility* f);
    void addWaitingList(ID,WaitingList&);
    ///
    ////GetDataSlots
    //
signals:
    void pressedAddBeds();
    void pressedAddFacilities();
    void pressedAddUserAccts();
    void pressedMovePatients();
    void pressedAddPatients();
    void pressedGenerateReport();
    void pressedViewAllReports();
    void pressedUpdateWaitingList();
private:
    void connectSlots(GetDataDisplayMapInterface&);
public:
    DisplayMapControl(GetDataDisplayMapInterface& inter,QObject* parent = 0);
    ~DisplayMapControl();
    void run();

private:
    Map* map;
};

#endif // DISPLAYMAPCONTROL_H

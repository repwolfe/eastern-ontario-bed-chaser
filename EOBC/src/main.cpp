#include <QtGui/QApplication>
#include "displaymapcontrol.h"
#include "logoncontrol.h"
#include "storageHandler.h"
#include "changedatacontrol.h"
#include "reportingcontrol.h"

int main(int argc, char *argv[])
{
    StorageHandler handler (QString(":/storage/resources/storage.xml"));
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();
    LogOnControl logControl;
    logControl.run();
    ChangeDataControl changeDataControl;
    ReportingControl rControl;
    rControl.run();

    //
    //CONNECT SUBSYSTEMS
    //

    QObject::connect(&logControl,SIGNAL(pressedEnter(int)),&mapControl,SLOT(getLoggedOn(int)));
    QObject::connect(&mapControl,SIGNAL(pressedAddBeds()),&changeDataControl,SLOT(displayUpdateBedsForm()));
    QObject::connect(&mapControl,SIGNAL(pressedAddFacilities()),&changeDataControl,SLOT(displayAddFacilityForm()));
    QObject::connect(&mapControl,SIGNAL(pressedAddPatients()),&changeDataControl,SLOT(displayMovePatientsToBedForm()));
    QObject::connect(&mapControl,SIGNAL(pressedAddUserAccts()),&changeDataControl,SLOT(displayCreateUserForm()));
    QObject::connect(&mapControl,SIGNAL(pressedMovePatients()),&changeDataControl,SLOT(displayMovePatientsToFacilityForm()));
    QObject::connect(&mapControl,SIGNAL(pressedGenerateReport()),&rControl,SLOT(showGenerateReportWindow()));
    QObject::connect(&mapControl,SIGNAL(pressedViewAllReports()),&rControl,SLOT(showViewAllReportsWindow()));
    //QObject::connect(&mapControl,SIGNAL(pressedUpdateWaitingList()),&changeDataControl,SLOT(displayMovePatientsToFacilityForm()));
    return a.exec();
}


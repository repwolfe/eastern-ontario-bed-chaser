#include <QtGui/QApplication>

#include "getdatacontrol.h"
#include "getdatadisplaymapinterface.h"
#include "getdatareportinginterface.h"

#include "displaymapcontrol.h"
#include "logoncontrol.h"
#include "storageHandler.h"
#include "changedatacontrol.h"
#include "reportingcontrol.h"
#include "communicationreceiveinterface.h"
#include "communicationsendinterface.h"
#include "sendchangedatainterface.h"
#include "ReceiveMessageControl.h"
#include "storagewrite.h"
#include "changedatareceiveinterface.h"

int main(int argc, char *argv[])
{
    StorageHandler handler (QString(":/storage/resources/storage.xml"));
    StorageWrite storageWrite(&handler);
    QApplication a(argc, argv);

    // Get Data and its interfaces
    GetDataControl getDataControl;
    GetDataChangeDataInterface gdChangeDataI(getDataControl);
    GetDataDisplayMapInterface gdDisplayMapI(getDataControl);
    GetDataReportingInterface gdReportingI(getDataControl);

    DisplayMapControl mapControl(gdDisplayMapI);
    LogOnControl logControl;
    logControl.run();
    ReportingControl rControl(gdReportingI);
    rControl.run();

    CommunicationSendInterface commSendI;
    SendMessageControl sendControl(commSendI);
    SendChangeDataInterface sendChangeDataI(sendControl);
    CommunicationReceiveInterface commReceiveI;
    ReceiveMessageControl receiveControl(commReceiveI);

    ChangeDataControl changeDataControl(gdChangeDataI, sendChangeDataI);

    ChangeDataReceiveInterface changeDataReceiveInterface(storageWrite,receiveControl);
    Q_UNUSED(changeDataReceiveInterface);
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
    QObject::connect(&mapControl,SIGNAL(pressedUpdateWaitingList()),&changeDataControl,SLOT(displayUpdateWaitingList()));
    return a.exec();
}


#include <QtGui/QApplication>
#include "displaymapcontrol.h"
#include "logoncontrol.h"
#include "storageHandler.h"
#include "changedatacontrol.h"

int main(int argc, char *argv[])
{
    StorageHandler handler (QString(":/storage/resources/storage.xml"));
    int i = 4;
    i++;
    //handler;
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();
    LogOnControl logControl;
    logControl.run();
    ChangeDataControl changeDataControl;
    changeDataControl.run();
    QObject::connect(&logControl,SIGNAL(pressedEnter(int)),&mapControl,SLOT(getLoggedOn(int)));
    return a.exec();
}

#include <QtGui/QApplication>
#include "displaymapcontrol.h"
#include "logoncontrol.h"
#include "storageHandler.h"
#include "changedatacontrol.h"

int main(int argc, char *argv[])
{
    int i = 4;
    i++;
    StorageHandler handler(QString(":/storage/bin/storage.txt"));
    //handler;
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();
    //LogOnControl logControl;
    //logControl.run();
    ChangeDataControl changeDataControl;
    changeDataControl.run();
    return a.exec();
}

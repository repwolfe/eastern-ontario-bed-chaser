#include <QtGui/QApplication>
#include "DisplayMap/displaymapcontrol.h"
#include "LogOn/logoncontrol.h"
#include "Storage/storageHandler.h"

int main(int argc, char *argv[])
{
    int i = 4;
    i++;
    StorageHandler handler (QString(":/storage/bin/storage.txt"));
    handler;
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();
    LogOnControl logControl;
    logControl.run();
    return a.exec();
}

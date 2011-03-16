#include <QtGui/QApplication>
#include "DisplayMap/displaymapcontrol.h"
#include "LogOn/logoncontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();
    LogOnControl logControl;
    logControl.run();
    return a.exec();
}

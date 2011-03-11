#include <QtGui/QApplication>
#include "DisplayMap/displaymapcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();

    return a.exec();
}

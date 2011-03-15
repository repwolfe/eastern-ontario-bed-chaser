#include <QtCore/QCoreApplication>
#include "DisplayMap/displaymapcontrol.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DisplayMapControl c;
    //c.run();
    return a.exec();
}

#include "displaymapcontrol.h"

DisplayMapControl::DisplayMapControl(QObject* parent) : QObject(parent)
{
    map = new Map();
    //map->setGeometry(QRect(90,0,1000,600));
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

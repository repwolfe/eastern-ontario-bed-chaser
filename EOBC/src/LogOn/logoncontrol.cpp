#include "logoncontrol.h"

LogOnControl::LogOnControl(QObject* parent) : QObject(parent), wind()
{
    //map = new Map();
    connect(&wind, SIGNAL(pressedEnter(int)),this,SLOT(getEnter(int)));
    //map->setGeometry(QRect(90,0,1000,600));
}
LogOnControl::~LogOnControl()
{
    //delete map;
}

void LogOnControl::run()
{
    //map->show();
     wind.show();
}
void LogOnControl::getEnter(int per)
{
    emit pressedEnter(per);
}



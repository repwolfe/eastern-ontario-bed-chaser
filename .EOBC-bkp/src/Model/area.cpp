#include "area.h"

Area::Area()
{
}

Area::~Area()
{
    QLinkedList<Facility*>::iterator iter = _facilities.begin();
    while (iter != _facilities.end())
    {
        delete *iter;
        ++iter;
    }
}

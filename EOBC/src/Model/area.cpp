#include "area.h"

Area::Area(WaitingList* inList)
    : _list(inList)
{

}

Area::~Area()
{
    delete _list;
}


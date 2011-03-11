#include "facility.h"

Facility::Facility()
{
}

Facility::~Facility()
{
    QLinkedList<Bed*>::iterator iter = _beds.begin();
    while (iter != _beds.end())
    {
        delete *iter;
        ++iter;
    }
}

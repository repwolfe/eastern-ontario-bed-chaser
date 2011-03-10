#ifndef AREA_H
#define AREA_H

#include <QLinkedList>
#include "facility.h"

class Area
{
public:
    Area();
    ~Area();

private:
    QLinkedList<Facility*> _facilities;
};

#endif // AREA_H

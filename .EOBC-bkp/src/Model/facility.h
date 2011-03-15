#ifndef FACILITY_H
#define FACILITY_H

#include <QLinkedList>
#include "bed.h"

class Facility
{
public:
    Facility();
    ~Facility();

private:
    QLinkedList<Bed*> _beds;
};

#endif // FACILITY_H

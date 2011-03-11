#ifndef FACILITY_H
#define FACILITY_H

#include "bed.h"
#include <QSet>

class Facility
{
public:
    Facility();
    ~Facility();

    void addBed(Bed* inBed);
    void deleteBed(Bed* inBed);
    void setBedList(QSet<Bed*>& inBeds);

private:
    void _deleteBeds();

    QSet<Bed*> _beds;
};

#endif // FACILITY_H

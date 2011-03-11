#include "facility.h"

Facility::Facility()
{
}

Facility::~Facility()
{
    _deleteBeds();
}

void Facility::addBed(Bed* inBed)
{
    _beds.insert(inBed);
}

void Facility::deleteBed(Bed* inBed)
{
    QSet<Bed*>::iterator bed = _beds.find(inBed);
    if (bed != _beds.end())
    {
        delete *bed;
        _beds.erase(bed);
    }
    _beds.remove(inBed);
}

void Facility::setBedList(QSet<Bed*>& inBeds)
{
    if (_beds != inBeds)
    {
        _deleteBeds();
        _beds = inBeds;
    }
}

void Facility::_deleteBeds()
{
    foreach(Bed* bed, _beds)
    {
        delete bed;
    }
    _beds.clear();
}

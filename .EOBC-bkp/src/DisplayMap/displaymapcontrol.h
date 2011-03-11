#ifndef DISPLAYMAPCONTROL_H
#define DISPLAYMAPCONTR

#include "map.h"

class DisplayMapControl
{
private:

public:
    DisplayMapControl();
    ~DisplayMapControl();
    void run();
private:
    Map* map;
};

#endif // DISPLAYMAPCONTROL_H

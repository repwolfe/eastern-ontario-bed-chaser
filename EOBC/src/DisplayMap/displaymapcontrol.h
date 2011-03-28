#ifndef DISPLAYMAPCONTROL_H
#define DISPLAYMAPCONTROL_H

#include "map.h"

class DisplayMapControl : public QObject
{
Q_OBJECT
public slots:
    void getLoggedOn(int);
private:

public:
    DisplayMapControl(QObject* parent = 0);
    ~DisplayMapControl();
    void run();

private:
    Map* map;
};

#endif // DISPLAYMAPCONTROL_H

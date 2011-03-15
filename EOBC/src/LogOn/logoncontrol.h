#ifndef LOGONCONTROL_H
#define LOGONCONTR

#include "logonwindow.h"

class LogOnControl
{
private:

public:
    LogOnControl();
    ~LogOnControl();
    void run();
private:
    LogOnWindow wind;
};

#endif // LOGONCONTROL_H

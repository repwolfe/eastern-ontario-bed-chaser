#ifndef LOGONCONTROL_H
#define LOGONCONTR

#include "logonwindow.h"

class LogOnControl : public QObject
{
    Q_OBJECT
signals:
    void pressedEnter(int);
public slots:
    void getEnter(int);
private:

public:
    LogOnControl(QObject* parent = 0);
    ~LogOnControl();
    void run();
private:
    LogOnWindow wind;
};

#endif // LOGONCONTROL_H

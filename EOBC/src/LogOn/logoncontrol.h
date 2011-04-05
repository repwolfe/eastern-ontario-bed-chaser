#ifndef LOGONCONTROL_H
#define LOGONCONTR

#include "logonwindow.h"

/** @brief LogOnControl is just a simple class that manages the LogOnWindow class
  * it has listeners to the buttons in the window so that it can handle the event of
  * the user logging in.
  * This class just stores the information from the LogOnWindow QWidget
  */

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
    void run();
private:
    LogOnWindow wind;
};

#endif // LOGONCONTROL_H

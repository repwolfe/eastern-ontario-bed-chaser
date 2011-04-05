#include "logoncontrol.h"

/** this is the constructor for LogOnControl
  * it connects the logon button from the LogOnWindow,
  * and calls the constructor for the LogOnWindow
  * @param parent just passed to the QObject constructor
  */

LogOnControl::LogOnControl(QObject* parent) : QObject(parent), wind()
{
    //map = new Map();
    connect(&wind, SIGNAL(pressedEnter(int)),this,SLOT(getEnter(int)));
    //map->setGeometry(QRect(90,0,1000,600));
}

 /** this method is called at system startup
   * it is designed just to show the logonwindow
   */
void LogOnControl::run()
{
    //map->show();
     wind.show();
}

 /** this method is a slot connected to the LogOnWindow's logon button
   * when selected, it sends a signal to the DisplayMapControl's slot so it can
   * show the Map window.
   * @param per Short for permissions. Sends the current permission level of the user logging on.
   */
void LogOnControl::getEnter(int per)
{
    emit pressedEnter(per);
}
/** this method is a slot connected to ChangeData's Make User Account button
  * when selected, it sends a signal to the DisplayMapControl's slot so it can
  * load the user accounts file, and append it to the end.
  * @param user The new username.
  * @param pass The new password.
  * @param ut The permission level of the user.
  */
void LogOnControl::receivedNewUserAccount(QString user, QString pass,Convenience::UserType ut)
{
    QFile file("../EOBC/resources/accounts.txt");
    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream in(&file);
        in<<user <<" "<<pass<<" "<< " "<<(int)ut;
    }
    else
    {
        qDebug("Sucks");
    }

    file.close();

}



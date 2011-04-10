#ifndef LOGONWINDOW_H
#define LOGONWINDOW_H

#include <QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QPainter>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <convenience.h>
#include "qmessagebox.h"

 /** @brief This class manages the logon window gui, and it also handles the checking for logging in.
   * it contains not persistant information, but a file is loaded every time login is pressed
   * the file is loaded, parsed, and checked with the current user input to see if it is valid to log in
   * a signal is then sent to DisplayMap so it can start up, and set it permissions
   */

class LogOnWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LogOnWindow(QWidget *parent = 0);

signals:
    void pressedEnter(int);
protected:
    void keyPressEvent(QKeyEvent *event);
public slots:
    void logIn();
private:
    QLabel* backgroundPic;
    QPushButton* logInButton;
    QPushButton* cancelButton;
    QLineEdit* usrBox;
    QLineEdit* passBox;
    int permissions;
    void loadBackground();
    void loadLayout();
};

#endif // LOGONWINDOW_H

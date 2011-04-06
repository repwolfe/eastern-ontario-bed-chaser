#include "logonwindow.h"
#define ENTER 16777220
#define HACK 0

 /** This is the constructor for LogOnWindow
   * it calls two helper functions to set up the layout and background
   * @param parent just sent to the QMainWindow constructor
   */


LogOnWindow::LogOnWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("EOBC : Log On");
    //resize(1000,800);
    setGeometry(Convenience::getCenterForSize(1000,650));
    loadBackground();
    loadLayout();
    permissions = -1;
}
/** This method is called from the constructor
  * it loads a background image from the resource file, and paints it onto the background
  */
void LogOnWindow::loadBackground()
{
    backgroundPic = new QLabel();
    QImage img(":/pics/resources/LHINLogo2.png");
    QImage fixedImage(1000,650, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.fillRect(QRect(0,0,1000,650), Qt::white);
    painter.drawImage(0,0,img);
    painter.end();
    backgroundPic->setPixmap(QPixmap::fromImage(fixedImage));

    setCentralWidget(backgroundPic);
}
/** This method sets up the GUI for the LogOnWindow
  * it adds two input boxes so the user can enter their username and password and two buttons to submit or cancel
  */
void LogOnWindow::loadLayout()
{
    QGridLayout *q = new QGridLayout();


    logInButton = new QPushButton("Log In");
    cancelButton = new QPushButton("Cancel");
    connect(logInButton,SIGNAL(clicked()),this,SLOT(logIn()));
    usrBox = new QLineEdit();
    passBox = new QLineEdit();

    q->setContentsMargins(300,350,330,130);
    q->setColumnStretch(1,150);
    q->setRowStretch(2,15);
    q->setRowStretch(3,15);
    q->setColumnStretch(0,150);

    q->addWidget(new QLabel("Username"),0,0);
    q->addWidget(new QLabel("Password"),0,1);
    q->addWidget(logInButton,2,0);
    q->addWidget(cancelButton,2,1);
    q->addWidget(usrBox,1,0);
    q->addWidget(passBox,1,1);
    passBox->setEchoMode(QLineEdit::Password);
    backgroundPic->setLayout(q);

}
/** This method is called from the "log in" button slot
  * it loads in the file that contains all the usernames and passwords, and compares them to the input from the user
  * if it is valid, the window closes and the permissions are set
  * otherwise, a popup window is shown yelling at the user for being stupid
  */
void LogOnWindow::logIn()
{
    bool correctInput = false;
    QFile file(":/logon/resources/accounts.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString curLine = in.readLine();
    while(curLine != "")
    {
        char curChar = curLine[0].toAscii();
        int index = 0;
        QString usr ="", pass="";
        while(curChar != ' ')
        {
            usr += curChar;
            index++;
            curChar = curLine[index].toAscii();
        }
        index++;
        curChar = curLine[index].toAscii();
        int curInt = -1;
        while(curInt != 32)
        {
            pass += curChar;
            index++;
            curChar = curLine[index].toAscii();
            curInt = curLine[index].toAscii();
        }  
        if(usr == usrBox->text() )
        {
            if(pass == passBox->text())
            {
                permissions = curLine[index+1].toAscii() -48;
                emit pressedEnter(permissions);
                correctInput = true;
                close();
            }
        }
        curLine = in.readLine();
    }
    if(!correctInput && !HACK)
    {
        QMessageBox mb;
        mb.setWindowTitle("Invalid Input");
        mb.setIcon(QMessageBox::Critical);
        mb.setText("Please enter in your username and password again");
        mb.exec();
    }

    //this->close();
}
/** This method is the listener to the key event of the window
  * it listenes to the enter key, and if pressed, the logIn method is called.
  */
void LogOnWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == ENTER)
    {
        logIn();
        if(HACK)
        {
            emit pressedEnter(2);
            close();
        }
    }
}

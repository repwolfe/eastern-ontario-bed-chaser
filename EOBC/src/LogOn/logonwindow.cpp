#include "logonwindow.h"
#define ENTER 16777220

LogOnWindow::LogOnWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("EOBC : Log On");
    resize(1000,800);
    setGeometry (100,0,1000,800);
    loadBackground();
    loadLayout();
}
void LogOnWindow::loadBackground()
{
    backgroundPic = new QLabel();
    QImage img(":/pics/LHINLogo2.png");
    QImage fixedImage(1000,800, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.fillRect(QRect(0,0,1000,800), Qt::white);
    painter.drawImage(0,0,img);
    painter.end();
    backgroundPic->setPixmap(QPixmap::fromImage(fixedImage));

    setCentralWidget(backgroundPic);
}
void LogOnWindow::loadLayout()
{
    QGridLayout *q = new QGridLayout();


    logInButton = new QPushButton("Log In");
    cancelButton = new QPushButton("Cancel");
    connect(logInButton,SIGNAL(clicked()),this,SLOT(logIn()));
    usrBox = new QLineEdit();
    passBox = new QLineEdit();

    q->setContentsMargins(300,300,330,330);
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


    //
   // passBox = new QLineEdit();
}
void LogOnWindow::logIn()
{
    QFile file(":/logon/bin/accounts.txt");
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
        while(curLine[index] != '\0')
        {
            pass += curChar;
            index++;
            curChar = curLine[index].toAscii();
        }
        if(usr == usrBox->text() )
        {
            if(pass == passBox->text())
                close();
        }
        curLine = in.readLine();
    }

    //this->close();
}
void LogOnWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == ENTER)
    {
        logIn();
        close();
    }
}

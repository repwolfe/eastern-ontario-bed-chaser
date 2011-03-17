#include "logonwindow.h"

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
    //usrBox = new QLineEdit();
    //passBox = new QLineEdit();
    q->setContentsMargins(300,10,300,10);
    q->setColumnStretch(1,150);
    q->setRowStretch(0,150);
    q->setColumnStretch(0,150);
    q->addWidget(logInButton,0,0);
    q->addWidget(cancelButton,0,1);
    backgroundPic->setLayout(q);
}

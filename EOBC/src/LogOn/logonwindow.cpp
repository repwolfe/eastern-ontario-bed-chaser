#include "logonwindow.h"

LogOnWindow::LogOnWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("EOBC : Log On");
    resize(1000,800);
    setGeometry (100,0,1000,800);
    backgroundPic = new QLabel();

    QImage img(":/pics/LHINLogo2.png");
    //backgroundPic.setGeometry(0,0,1000,800);
    QImage fixedImage(1000,800, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.fillRect(QRect(0,0,1000,800), Qt::white);
    //painter.drawImage(QPoint(),*image);
    painter.end();
    backgroundPic->setPixmap(QPixmap::fromImage(img));
   // layout();
    setCentralWidget(backgroundPic);

}

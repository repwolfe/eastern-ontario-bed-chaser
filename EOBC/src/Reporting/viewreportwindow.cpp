#include "viewreportwindow.h"

ViewReportWindow::ViewReportWindow(Report* __report, QWidget *parent) :
    QWidget(parent)
{
    int scaleFactor = 50;
    QGridLayout grid;
    background = new QLabel();
    grid.addWidget(background,0,0);
    setLayout(&grid);
    this->__report = __report;
    this->setMinimumWidth(500);
    setGeometry(Convenience::getCenterForSize(300+__report->getBarNum()*scaleFactor,450));
    setWindowTitle("Report: "+__report->getDate());

    if(300+__report->getBarNum()*scaleFactor>500)
        setFixedSize(300+__report->getBarNum()*scaleFactor,450);
    else
        setFixedSize(500,450);

    //if(100+__report->getBarNum()*scaleFactor>300)
        __report->setWidth(100+__report->getBarNum()*scaleFactor);
}
ViewReportWindow::~ViewReportWindow()
{

}

void ViewReportWindow::paintEvent(QPaintEvent *)
{
    //QImage r(500,500,QImage::Format_ARGB32_Premultiplied);
    QPainter g(this);
    __report->draw(g);
    //background->setPixmap(QPixmap::fromImage(r));
}

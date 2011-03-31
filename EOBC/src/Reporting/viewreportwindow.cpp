#include "viewreportwindow.h"

ViewReportWindow::ViewReportWindow(Report* __report, QWidget *parent) :
    QWidget(parent)
{
    QGridLayout grid;
    background = new QLabel();
    grid.addWidget(background,0,0);
    setLayout(&grid);
    this->__report = __report;
    setGeometry(Convenience::getCenterForSize(500,450));
    setWindowTitle("Report: "+__report->getDate());
    setFixedSize(500,450);
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

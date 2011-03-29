#include "viewreportwindow.h"

ViewReportWindow::ViewReportWindow(Report* report, QWidget *parent) :
    QWidget(parent)
{
    QGridLayout grid;
    background = new QLabel();
    grid.addWidget(background,0,0);
    setLayout(&grid);
    this->report = report;
    setGeometry(Convenience::getCenterForSize(500,450));
    setWindowTitle("Report: "+report->getDate());
    setFixedSize(500,450);
}
void ViewReportWindow::paintEvent(QPaintEvent *)
{
    QImage r(500,500,QImage::Format_ARGB32_Premultiplied);
    QPainter g(this);
    report->draw(g);
    background->setPixmap(QPixmap::fromImage(r));
}

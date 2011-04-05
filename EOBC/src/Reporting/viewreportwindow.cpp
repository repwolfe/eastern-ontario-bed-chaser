#include "viewreportwindow.h"
/** This is the constructor for ViewReportWindow
  * sets up the form to be the correct size so it can fit the data in the report.
  * @param __report the pointer to the report object that is stored so that it can be drawn
  * @param parent just sent to the QWidget constructor
  */


ViewReportWindow::ViewReportWindow(Report* __report, QWidget *parent) :
    QWidget(parent)
{
    int scaleFactor = 50;
    QGridLayout grid;
    background = new QLabel();
    grid.addWidget(background,0,0);
    setLayout(&grid);
    this->__report = __report;


    int height = 430 + __report->getFacilNum()*30;
    this->setMinimumWidth(500);
    setGeometry(Convenience::getCenterForSize(300+__report->getBarNum()*scaleFactor,height));
    setWindowTitle("Report: "+__report->getDate());

    if(300+__report->getBarNum()*scaleFactor>500)
        setFixedSize(300+__report->getBarNum()*scaleFactor,height);
    else
        setFixedSize(500,height);

    //if(100+__report->getBarNum()*scaleFactor>300)
        __report->setWidth(100+__report->getBarNum()*scaleFactor);
        __report->setHeight(height);
}
/** the paint event for ViewReportWindow
  * called every 60 seconds.
  * generates a QPainter object that will allow things to be drawn to the background of the window
  * the report is then asked to draw itself based on the QPainter
  */

void ViewReportWindow::paintEvent(QPaintEvent *)
{
    //QImage r(500,500,QImage::Format_ARGB32_Premultiplied);
    QPainter g(this);
    __report->draw(g);
    //background->setPixmap(QPixmap::fromImage(r));
}

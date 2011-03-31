#include "viewallreportswindow.h"

ViewAllReportsWindow::ViewAllReportsWindow(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel("Reports"),0,0);
    layout->addWidget(new QLabel(),0,1);
    reportsBox = new QListWidget();

    layout->addWidget(reportsBox,1,0,1,0);
    QPushButton* select = new QPushButton("Select");
    layout->addWidget(select,2,0);
    connect(select,SIGNAL(pressed()),this,SLOT(pressedSelectSlot()));

    QPushButton* cancel = new QPushButton("Cancel");
    layout->addWidget(cancel,3,0);
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    setLayout(layout);
    layout->setContentsMargins(30,10,30,10);
    setGeometry(Convenience::getCenterForSize(400,350));

    //
    //DELETE THIS
    //

    //wind = new ViewReportWindow(new Report(bars));
    //wind->show();
}
void ViewAllReportsWindow::pressedSelectSlot()
{
    emit pressedSelect(reportsBox->currentIndex().row());
}
void ViewAllReportsWindow::addItem(Report* r)
{
    reportsBox->addItem("Report: "+ r->getDate());
}
void ViewAllReportsWindow::pressedCancelSlot()
{
    close();
}



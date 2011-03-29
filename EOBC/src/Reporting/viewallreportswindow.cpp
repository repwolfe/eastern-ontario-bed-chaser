#include "viewallreportswindow.h"

ViewAllReportsWindow::ViewAllReportsWindow(QWidget *parent) :
    QWidget(parent)
{

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel("Reports"),0,0);
    layout->addWidget(new QLabel(),0,1);
    QListWidget* reportsBox = new QListWidget();
    reportsBox->addItem("Report Submitted: Jan 4th 2011");
    reportsBox->addItem("Report Submitted: Jan 14th 2011");
    reportsBox->addItem("Report Submitted: Jan 15th 2011");

    layout->addWidget(reportsBox,1,0,1,0);

    layout->addWidget(new QPushButton("Select"),2,0);
    layout->addWidget(new QPushButton("Cancel"),3,0);
    setLayout(layout);
    layout->setContentsMargins(30,10,30,10);
    setGeometry(Convenience::getCenterForSize(400,350));
}


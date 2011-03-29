#include "generatereportwindow.h"
#include "convenience.h"
GenerateReportWindow::GenerateReportWindow(QWidget *parent) :
    QWidget(parent)
{
    int height = 0;
    this->setWindowTitle("Generate Report");
    layout.addWidget(new QLabel("Facility"),height,0);
    layout.addWidget(new QLabel("Date(s)"),height++,1);

    QComboBox* facilities = new QComboBox();
    facilities->addItem("Franklin Hospital");
    facilities->addItem("Franklin Hospital");
    layout.addWidget(facilities,height,0);

    layout.addWidget(new QLineEdit(),height++,1);

    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER

    layout.addWidget(new QLabel("Constraints"),height++,0);
    QComboBox* constraints = new QComboBox();
    constraints->addItem("Waiting List");
    constraints->addItem("Occupancy Rates");
    layout.addWidget(constraints,height++,0,1,0);

    layout.addWidget(new QLabel(),height++,0); ///////////SPACER

    layout.addWidget(new QPushButton("Submit"),height++,0);
    layout.addWidget(new QPushButton("Cancel"),height++,0);

    layout.addWidget(new QLabel(),height++,0); ///////////SPACER

    layout.setRowMinimumHeight(0,10);
    //layout.setRowMinimumHeight(1,100);
    layout.setRowMinimumHeight(2,10);
    //layout.setRowMinimumHeight(3,100);
    layout.setContentsMargins(30,10,30,10);
    setGeometry(Convenience::getCenterForSize(400,350));

    setLayout(&layout);
}



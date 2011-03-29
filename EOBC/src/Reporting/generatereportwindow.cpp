#include "generatereportwindow.h"
#include "convenience.h"
GenerateReportWindow::GenerateReportWindow(QWidget *parent) :
    QWidget(parent)
{
    int height = 0;
    this->setWindowTitle("Generate Report");
    layout.addWidget(new QLabel("Facility"),height,0,Qt::AlignTop);
    layout.addWidget(new QLabel("Date(s)"),height++,1,Qt::AlignTop);

    QComboBox* facilities = new QComboBox();
    facilities->addItem("Franklin Hospital");
    facilities->addItem("Franklin Hospital");
    layout.addWidget(facilities,height,0,Qt::AlignTop);

     //////////////////////////////////////////////////////////DATES

    dateStartEntry = new QDateEdit();
    dateStartEntry->setDisplayFormat("MMMM d yyyy");
    dateStartEntry->setDate(QDate::currentDate());
    layout.addWidget(dateStartEntry,height,1,Qt::AlignTop);
    dateEndEntry = new QDateEdit();
    dateEndEntry->setDisplayFormat("MMMM d yyyy");
    dateEndEntry->setDate(QDate::currentDate());
    layout.addWidget(dateEndEntry,height++,2,Qt::AlignTop);


    layout.addWidget(new QLabel(),height++,0); ///////////SPACER

    layout.addWidget(new QLabel("Constraints"),height++,0,Qt::AlignTop);
    QComboBox* constraints = new QComboBox();
    constraints->addItem("Waiting List");
    constraints->addItem("Occupancy Rates");
    //layout.addWidget(new QLabel(),height+1,1,Qt::AlignTop);
    layout.addWidget(constraints,height,0,1,1,Qt::AlignTop);

    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER
    layout.addWidget(new QLabel(),height,1); ///////////SPACER

    QPushButton* submit = new QPushButton("Submit");
    connect(submit,SIGNAL(clicked()),this,SLOT(pressedSubmit()));
    layout.addWidget(submit,height++,2,Qt::AlignTop);
    layout.addWidget(new QPushButton("Cancel"),height,2,Qt::AlignTop);

    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER

    layout.setRowStretch(0,0);
    layout.setRowStretch(1,0);
    layout.setRowStretch(2,110);
    layout.setRowStretch(3,0);
    layout.setRowStretch(4,0);
    layout.setRowStretch(5,0);
    //layout.setRowMinimumHeight(3,100);
    layout.setContentsMargins(30,10,30,10);
    setGeometry(Convenience::getCenterForSize(500,200));
    this->setFixedSize(500,200);
    setLayout(&layout);
}
void GenerateReportWindow::pressedSubmit()
{
    QVector<ReportBars*> bars;
    int barLengths1[] = {12+rand()%7,12+rand()%7,12+rand()%7};
    bars.push_back(new ReportBars(barLengths1));
    int barLengths2[] = {13+rand()%7,13+rand()%7,13+rand()%7};
    bars.push_back(new ReportBars(barLengths2));
    int barLengths3[] = {14+rand()%7,14+rand()%7,14+rand()%7};
    bars.push_back(new ReportBars(barLengths3));
    int barLengths4[] = {15+rand()%7,15+rand()%7,15+rand()%7};
    bars.push_back(new ReportBars(barLengths4));
    int barLengths5[] = {16+rand()%7,16+rand()%7,16+rand()%7};
    bars.push_back(new ReportBars(barLengths5));
    int barLengths6[] = {17+rand()%7,17+rand()%7,17+rand()%7};
    bars.push_back(new ReportBars(barLengths6));
    Report* rep = new Report(dateStartEntry->text() + "-"+dateEndEntry->text(),bars);

    emit reportGenerated(rep);
}



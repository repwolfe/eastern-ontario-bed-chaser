#include "generatereportwindow.h"
#include "convenience.h"
GenerateReportWindow::GenerateReportWindow(QWidget *parent) :
    QWidget(parent)
{

    int height = 0;
    this->setWindowTitle("Generate Report");
    layout.addWidget(new QLabel("Facility"),height,0,Qt::AlignTop);
    layout.addWidget(new QLabel("Date(s)"),height++,1,Qt::AlignTop);

    facilities = new QComboBox();
    facilToRows = new QMap<int,ID>();


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
    constraints = new QComboBox();
    constraints->addItem("Waiting List");
    constraints->addItem("Occupancy Rates");
    //layout.addWidget(new QLabel(),height+1,1,Qt::AlignTop);
    layout.addWidget(constraints,height,0,1,1,Qt::AlignTop);

    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER
    layout.addWidget(new QLabel(),height,1); ///////////SPACER

    QPushButton* submit = new QPushButton("Submit");
    connect(submit,SIGNAL(clicked()),this,SLOT(pressedSubmit()));
    layout.addWidget(submit,height++,2,Qt::AlignTop);
    QPushButton* cancel = new QPushButton("Cancel");
    layout.addWidget(cancel,height,2,Qt::AlignTop);

    connect(cancel,SIGNAL(clicked()),this,SLOT(pressedCancel()));

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
    // FOR TESTING ONLY
    // FOR TESTING ONLY
    // FOR TESTING ONLY
    QVector<ReportBars*> bars;
    int barnum = 0;
    int dateType = 0;
    if(dateEndEntry->date().month() - dateStartEntry->date().month() == 0)
    {
        barnum= dateEndEntry->date().day() - dateStartEntry->date().day();
    }
    else if(dateEndEntry->date().year() - dateStartEntry->date().year() == 0)
    {
       barnum= dateEndEntry->date().month() - dateStartEntry->date().month();
       dateType = 1;
    }
    else
    {
       barnum= dateEndEntry->date().year() - dateStartEntry->date().year();
       dateType = 2;
    }
    for(int i=0;i<=barnum;i++)
    {
        int* barHeights = new int[4];
        barHeights[0]=rand()%(11+i)+10;
        barHeights[1]=rand()%(11+i)+10;
        barHeights[2]=0;//rand()%(11+i)+10;
        barHeights[3]=0;//100-(barHeights[0]+barHeights[1]+barHeights[2]);

        QString* barTypes = new QString[4];

        barTypes[0]="CCC";
        barTypes[1]="AC";
        barTypes[2]="CCC Open";
        barTypes[3]="AC Open";

        bars.push_back(new ReportBars(barHeights,barTypes));
    }
    Report* rep = new Report(dateStartEntry->text() + "-"+dateEndEntry->text(),dateStartEntry->date(),bars,(int)Convenience::HOSPITAL,dateType,facilities->currentText());

    emit reportGenerated(rep);
    // FOR TESTING ONLY
    // FOR TESTING ONLY
    // FOR TESTING ONLY

    // REAL CODE
    // REAL CODE
    // REAL CODE
    emit sendReportRequest(dateStartEntry->date(),
                           dateEndEntry->date(),
                           facilToRows->value(facilities->currentIndex()),
                           constraints->currentText());

    QMessageBox mb;
    mb.setWindowTitle("Report Submitted");
    mb.setIcon(QMessageBox::Information);
    mb.setText("Report Submitted. \nGo to Reports-> View Reports");
    mb.exec();

    close();
    // REAL CODE
    // REAL CODE
    // REAL CODE
}
void GenerateReportWindow::updateFacilities(const QMap<ID,QString>* facils)
{
    __facils = facils;
    facilities->clear();
    facilToRows = new QMap<int,ID>();
    foreach(ID i , facils->keys())
    {
        QString data = facils->find(i).value();
        facilities->addItem(data);
        facilities->update();
        facilToRows->insert(facilities->count()-1,i);
    }
}
void GenerateReportWindow::pressedCancel()
{
    close();
}



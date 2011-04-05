#include "generatereportwindow.h"
#include "convenience.h"
 /** Constructor for GenerateReportWindow
   * initializes buttons and widgets along with initializing empty lists for the facilities
   * @param parent does nothing
   */
GenerateReportWindow::GenerateReportWindow(QWidget *parent) :
    QWidget(parent)
{

    int height = 0;
    this->setWindowTitle("Generate Report");
    layout.addWidget(new QLabel("Facility"),height,0,Qt::AlignTop);
    layout.addWidget(new QLabel("Date(s)"),height++,2,Qt::AlignTop);

    facilities = new QListWidget();
    facilToRows = new QMap<int,ID>();


    layout.addWidget(facilities,height,0,5,2,Qt::AlignTop);

     //////////////////////////////////////////////////////////DATES

    dateStartEntry = new QDateEdit();
    dateStartEntry->setDisplayFormat("MMMM d yyyy");
    dateStartEntry->setDate(QDate::currentDate());
    layout.addWidget(dateStartEntry,height++,2,Qt::AlignTop);
    dateEndEntry = new QDateEdit();
    dateEndEntry->setDisplayFormat("MMMM d yyyy");
    dateEndEntry->setDate(QDate::currentDate());
    layout.addWidget(new QLabel("To"),height++,2,Qt::AlignTop);
    layout.addWidget(dateEndEntry,height++,2,Qt::AlignTop);
    layout.addWidget(new QLabel("Constraints"),height++,2,Qt::AlignTop);
    constraints = new QComboBox();
    constraints->addItem("Waiting List");
    constraints->addItem("Occupancy Rates");
    layout.addWidget(constraints,height++,2,Qt::AlignTop);

    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER


    //layout.addWidget(new QLabel(),height+1,1,Qt::AlignTop);


    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER
  //  layout.addWidget(new QLabel(),height,1); ///////////SPACER

    QPushButton* submit = new QPushButton("Submit");
    connect(submit,SIGNAL(clicked()),this,SLOT(pressedSubmit()));
    layout.addWidget(submit,height,0,Qt::AlignTop);
    QPushButton* cancel = new QPushButton("Cancel");
    layout.addWidget(cancel,height,1,Qt::AlignTop);

    connect(cancel,SIGNAL(clicked()),this,SLOT(pressedCancel()));

    //layout.addWidget(new QLabel(),height++,0); ///////////SPACER

    layout.setRowStretch(0,0);
    layout.setRowStretch(1,0);
    layout.setRowStretch(2,0);
    layout.setRowStretch(3,0);
    layout.setRowStretch(4,0);
    layout.setRowStretch(5,110);
    dateStartEntry->setMaximumDate(QDate::currentDate());
    dateEndEntry->setMaximumDate(QDate::currentDate());
    //layout.setRowMinimumHeight(3,100);
    layout.setContentsMargins(30,10,30,10);
    setGeometry(Convenience::getCenterForSize(500,300));
    this->setFixedSize(500,300);
    setLayout(&layout);
}
 GenerateReportWindow::~GenerateReportWindow()
{
    delete facilToRows;
}

/** pressedSubmit is the submit button slot for GenerateReportWindow
  * for testing, it generates a phony report while in reality it will just
  * send a signal with the data from the widgets to reportingControl
  */
void GenerateReportWindow::pressedSubmit()
{
    // FOR TESTING ONLY
    // FOR TESTING ONLY
    // FOR TESTING ONLY
    QVector<ReportBars*> bars;
    int barnum = 0;
    int dateType = 0;
    QList<QListWidgetItem*> items = facilities->selectedItems();
    QVector<QString> facilNames;
    for(int i =0;i<items.count();i++)
    {
        facilNames.push_back( items.at(i)->text());
    }
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
        QVector<int> barHeights;

        //barHeights[2]=0;//rand()%(11+i)+10;
        //barHeights[3]=0;//100-(barHeights[0]+barHeights[1]+barHeights[2]);

        QVector<QString> barTypes;
        if(facilNames.count()==1)
        {

            barTypes.push_back("CCC ");
            barTypes.push_back("AC  ");
            barTypes.push_back("CCCOpen");
            barTypes.push_back("ACOpen");
            barHeights.push_back(rand()%(11+i)+10);
            barHeights.push_back(rand()%(11+i)+10);
        }
        else
        {
            for(int j=0;j<facilNames.count();j++)
            {
                barTypes.push_back(facilNames.at(j));
                barHeights.push_back(rand()%(11+j)+10);
            }
        }

        bars.push_back(new ReportBars(barHeights,barTypes));
    }

    Report* rep = new Report(dateStartEntry->text() + "-"+dateEndEntry->text(),dateStartEntry->date(),bars,(int)Convenience::HOSPITAL,dateType,facilNames);

    emit reportGenerated(rep);
    // FOR TESTING ONLY
    // FOR TESTING ONLY
    // FOR TESTING ONLY

    // REAL CODE
    // REAL CODE
    // REAL CODE
    emit sendReportRequest(dateStartEntry->date(),
                           dateEndEntry->date(),
                           facilToRows->value(facilities->currentRow()),
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
/** updateFacilities is the slot that is called when a signal is recieved from GetData
  * updates all facilities in the QListWidget, and the QMap that maps the Facil ID to the row
  * @param facils the data received from GetData, contains all facil names
  */
void GenerateReportWindow::updateFacilities(const QMap<ID,QString>* facils)
{
    __facils = facils;
    facilities->clear();
    facilToRows = new QMap<int,ID>();
    foreach(ID i , facils->keys())
    {
        QString data = facils->find(i).value();
        QListWidgetItem* item = new QListWidgetItem(data);
        facilities->addItem(item);
        facilities->update();
        facilities->setSelectionMode(QAbstractItemView::MultiSelection);
        facilToRows->insert(facilities->count()-1,i);
    }
    facilities->setCurrentIndex(facilities->indexAt(QPoint(0,0)));
}
/** pressedCancel is the slot thats called when the cancel button is pressed
  * closes the window
  *
  */
void GenerateReportWindow::pressedCancel()
{
    close();
}



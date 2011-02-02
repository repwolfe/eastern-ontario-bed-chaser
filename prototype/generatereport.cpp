#include "generatereport.h"
#include "ui_generatereport.h"

GenerateReport::GenerateReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateReport)
{
    ui->setupUi(this);
    this->setWindowTitle("Generate Report");
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(closeButtonSlot()));
}

GenerateReport::~GenerateReport()
{
    delete ui;
}
void GenerateReport::closeButtonSlot()
{
    this->close();
}


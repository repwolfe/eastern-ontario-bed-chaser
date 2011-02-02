#include "updatewaitinglist.h"
#include "ui_updatewaitinglist.h"

UpdateWaitingList::UpdateWaitingList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateWaitingList)
{
    ui->setupUi(this);
    this->setWindowTitle("Update Waiting List");
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(closeButtonSlot()));
}

UpdateWaitingList::~UpdateWaitingList()
{
    delete ui;
}
void UpdateWaitingList::closeButtonSlot()
{
    this->close();
}

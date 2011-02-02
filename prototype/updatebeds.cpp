#include "updatebeds.h"
#include "ui_updatebeds.h"

UpdateBeds::UpdateBeds(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateBeds)
{
    ui->setupUi(this);
    this->setWindowTitle("Update Beds");
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(closeSlot()));
}

UpdateBeds::~UpdateBeds()
{
    delete ui;
}
 void UpdateBeds::closeSlot()
 {
     this->close();
 }

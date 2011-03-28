#include "updatewaitinglistform.h"

#include "convenience.h"

#include <QGridLayout>
#include <QLabel>

UpdateWaitingListForm::UpdateWaitingListForm(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Update Waiting List");

    int width = 520;
    int height = 300;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
    _setupConnections();
}

const QString UpdateWaitingListForm::getCurrentPatient() const
{
    return _patientList->currentItem()->text();
}

void UpdateWaitingListForm::_setupConnections()
{
    connect(_addPatientButton, SIGNAL(clicked()), SLOT(_addPatientClicked()));
    connect(_removePatientButton, SIGNAL(clicked()), SLOT(_removePatientClicked()));
    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelClicked()));
}

void UpdateWaitingListForm::_setupLayout()
{
    _patientList            = new QListWidget();
    _facilityList           = new QComboBox();

    _patientList->setSelectionMode(QAbstractItemView::SingleSelection);

    _addPatientButton       = new QPushButton("Add Patient");
    _removePatientButton    = new QPushButton("Remove Patient");
    _submitButton           = new QPushButton("Update");
    _cancelButton           = new QPushButton("Cancel");

    const int minWidth = 125;
    _addPatientButton->setMinimumWidth(minWidth);
    _removePatientButton->setMinimumWidth(minWidth);
    _submitButton->setMinimumWidth(minWidth);
    _cancelButton->setMinimumWidth(minWidth);

    QGridLayout* q = new QGridLayout();
    q->setColumnMinimumWidth(1, 150);
    for (int i = 0; i < 3; ++i) { q->setRowStretch(i, 0); }
    for (int i = 3; i < 6; ++i) { q->setRowStretch(i,100); }
    q->addWidget(new QLabel("Waiting List"), 0, 0);
    q->addWidget(new QLabel("From Facility"), 0, 1);
    q->addWidget(_patientList, 1, 0, 5, 1);
    q->addWidget(_facilityList, 1, 1);
    q->addWidget(_addPatientButton, 2, 1, Qt::AlignBottom);
    q->addWidget(_removePatientButton, 3, 1, Qt::AlignTop);
    q->addWidget(_submitButton, 4, 1);
    q->addWidget(_cancelButton, 5, 1);
    setLayout(q);
}

/************** PRIVATE SLOTS ***************/
void UpdateWaitingListForm::_submitClicked()
{
    emit submitClicked();
}

void UpdateWaitingListForm::_cancelClicked()
{
    close();
}

void UpdateWaitingListForm::_addPatientClicked()
{
    emit addPatientClicked();
}

void UpdateWaitingListForm::_removePatientClicked()
{
    emit removePatientClicked();
}

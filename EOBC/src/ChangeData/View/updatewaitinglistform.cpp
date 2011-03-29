#include "updatewaitinglistform.h"

#include "convenience.h"

#include <QGridLayout>
#include <QLabel>

UpdateWaitingListForm::UpdateWaitingListForm(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Update Waiting List");

    int width = 575;
    int height = 300;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
    _setupConnections();
}

/**
 * Returns the currently selected patient's health card number
 *
 * @return the health card number
 */
const QString UpdateWaitingListForm::getCurrentPatient() const
{
    return _patientList->currentItem()->text(1);
}

void UpdateWaitingListForm::addPatientItem(QString name, QString hcn)
{
    QStringList info(name);
    info.push_back(hcn);
    _patientList->insertTopLevelItem(0, new QTreeWidgetItem((QTreeWidget*)0, info));
}

void UpdateWaitingListForm::removeSelectedPatientItem()
{
    _patientList->takeTopLevelItem(_patientList->indexOfTopLevelItem(_patientList->currentItem()));
}

bool UpdateWaitingListForm::isPatientInList(QString hcn) const
{
    return !_patientList->findItems(hcn, Qt::MatchExactly, 1).empty();
}

void UpdateWaitingListForm::setPatientItems(const QMap<QString,QString>& inPatients)
{
    _patientList->clear();
    if (inPatients.size() > 0)
    {
        QList<QTreeWidgetItem*> items;
        QMap<QString,QString>::const_iterator iter = inPatients.begin();
        while (iter != inPatients.end())
        {
            QStringList info(iter.key());
            info.push_back(iter.value());
            items.append(new QTreeWidgetItem((QTreeWidget*)0, info));
            ++iter;
        }
        _patientList->insertTopLevelItems(0, items);
    }
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
    _facilityList           = new QComboBox();

    _patientList            = new QTreeWidget();
    _patientList->setSelectionMode(QAbstractItemView::SingleSelection);
    _patientList->setColumnCount(2);    // For Name and Hcn
    QStringList headers = (QStringList() << "Patient Name" << "Health Card Number");
    _patientList->setHeaderLabels(headers);
    _patientList->setColumnWidth(0, 250);
    _patientList->setSortingEnabled(true);

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
    emit cancelClicked();
}

void UpdateWaitingListForm::_addPatientClicked()
{
    emit addPatientClicked();
}

void UpdateWaitingListForm::_removePatientClicked()
{
    emit removePatientClicked();
}

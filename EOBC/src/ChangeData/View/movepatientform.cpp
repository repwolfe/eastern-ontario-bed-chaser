#include "movepatientform.h"
#include "convenience.h"

#include <QGridLayout>
#include <QLabel>

/**
 * Constructor for MovePatientForm
 *
 * @param title The Window Title
 * @param displayBedType True if it should have the Patient's bed type, False otherwise
 * @param moveTo String of where the patient is moved to (Bed or Facility)
 * @param parent the parent widget (optional)
 */
MovePatientForm::MovePatientForm(QString title, bool displayBedType, QString moveTo, bool displayAddRemove, QWidget *parent) :
    QWidget(parent), _displayBedType(displayBedType),
    _displayAddRemove(displayAddRemove), _moveToLabel(moveTo)
{
    setWindowTitle(title);

    int width = 575;
    int height = 300;

    // For now make these NULL
    _addPatientButton = 0;
    _removePatientButton = 0;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
    _setupConnections();
}

/**
 * Set the items of the Facility combo box, removes the old ones
 *
 * @param items a list of values to insert into it
 */
void MovePatientForm::setFacilityItems(QStringList& items)
{
    _facilityList->clear();
    _facilityList->insertItems(0, items);
}

/**
 * Set the items of the Move To combo box, removes the old ones
 *
 * @param items a list of values to insert into it
 */
void MovePatientForm::setMoveToItems(QStringList& items)
{
    _moveToList->clear();
    _moveToList->insertItems(0, items);
}

/**
 * Set the items of the Patient list, removes the old ones
 * Used for rows containing Patient Name and Health Card Number
 *
 * @param inPatients map of Patient Name to Health Card Number
 */
void MovePatientForm::setPatientItems(const QMap<QString, QString> &inPatients)
{
    _setPatientItems(inPatients);
}

/**
 * Set the items of the Patient list, removes the old ones
 * Used for rows containing Patient Name, Health Card Number and Bed Type
 *
 * @param nameToHcn map of Patient Name to Health Card Number
 * @param hcnToBed map of Health Card Number to Bed
 */
void MovePatientForm::setPatientItems(const QMap<QString,QString>& nameToHcn, const QMap<QString,QString>& hcnToBed)
{
    _setPatientItems(nameToHcn, &hcnToBed);
}

/**
 * Helper function to avoid code repetition for setPatientItems
 */
void MovePatientForm::_setPatientItems(const QMap<QString,QString>& nameToHcn, const QMap<QString,QString>* hcnToBed)
{
    _patientList->clear();
    bool includeBeds = false;
    if (nameToHcn.size() > 0)
    {
        if (hcnToBed && hcnToBed->size() > 0)
        {
            includeBeds = true;
        }
        QList<QTreeWidgetItem*> items;
        QMap<QString,QString>::const_iterator iter = nameToHcn.begin();
        while (iter != nameToHcn.end())
        {
            QStringList info(iter.key());
            info << iter.value();
            if (includeBeds)
            {
                QMap<QString,QString>::const_iterator bedFind = hcnToBed->find(iter.value());
                if (bedFind != hcnToBed->end())
                {
                    info << bedFind.value();
                    items.append(new QTreeWidgetItem((QTreeWidget*)0, info));
                }
            }
            else
            {
                items.append(new QTreeWidgetItem((QTreeWidget*)0, info));
            }
            ++iter;
        }
        _patientList->insertTopLevelItems(0, items);
        if (!items.isEmpty())
        {
            _patientList->setCurrentItem(items.first());
            _moveToList->setEnabled(true);
        }
    }
    else
    {
        _moveToList->setEnabled(false);
    }
}

void MovePatientForm::addPatientItem(QString name, QString hcn)
{
    QStringList info(name);
    info.push_back(hcn);
    _patientList->insertTopLevelItem(0, new QTreeWidgetItem((QTreeWidget*)0, info));
}

void MovePatientForm::removeSelectedPatientItem()
{
    _patientList->takeTopLevelItem(_patientList->indexOfTopLevelItem(_patientList->currentItem()));
}

/**
 * Let's you remove an item with a specific string from the facility list
 *
 * @param item to remove
 */
void MovePatientForm::removeFacilityItem(QString& item)
{
    _facilityList->removeItem(_facilityList->findText(item));
}

int MovePatientForm::getCurrentPatientRow()
{
   return _patientList->indexOfTopLevelItem(_patientList->currentItem());
}

/**
 * Returns the current patient's health card number if something is selected
 *
 * @param outHcn out parameter with the health card number of the selected patient, otherwise doesn't touch it
 *
 * @return True if a patient is selected, False otherwise
 */
bool MovePatientForm::getCurrentPatient(QString& outHcn) const
{
    QTreeWidgetItem* selection = _patientList->currentItem();
    if (selection)
    {
        outHcn = selection->text(1);
        return true;
    }
    return false;
}

void MovePatientForm::setCurrentMoveToItem(int index)
{
    _moveToList->setCurrentIndex(index);
}

bool MovePatientForm::isPatientInList(QString hcn) const
{
    return !_patientList->findItems(hcn, Qt::MatchExactly, 1).empty();
}

void MovePatientForm::_setupLayout()
{
    _facilityList   = new QComboBox();
    _moveToList     = new QComboBox();

    _patientList    = new QTreeWidget();
    _patientList->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList headers = (QStringList() << "Patient Name" << "Health Card Number");
    if (_displayBedType)
    {
        _patientList->setColumnCount(3);    // For Name, Hcn and Bed
        headers << "Bed";
    }
    else
    {
        _patientList->setColumnCount(2);    // For Name and Hcn
    }
    _patientList->setHeaderLabels(headers);
    _patientList->setColumnWidth(0, 250);
    if (_displayBedType) { _patientList->setColumnWidth(2, 40); }
    _patientList->setSortingEnabled(true);

    _moveToList->setEnabled(false);

    _submitButton   = new QPushButton("Submit");
    _cancelButton   = new QPushButton("Cancel");

    _submitButton->setMinimumWidth(125);
    _cancelButton->setMinimumWidth(125);

    int patientSpan;
    _displayAddRemove ? patientSpan = 7 : patientSpan = 5;

    QGridLayout* q = new QGridLayout();
    q->setColumnMinimumWidth(1, 150);
    for (int i = 0; i < 3; ++i) { q->setRowStretch(i, 0); }
    for (int i = 3; i < 6; ++i) { q->setRowStretch(i,100); }
    q->addWidget(new QLabel("Patients"), 0, 0);
    q->addWidget(new QLabel("From Facility"), 0, 1);
    q->addWidget(_patientList, 1, 0, patientSpan, 1);
    q->addWidget(_facilityList, 1, 1);
    q->addWidget(new QLabel(_moveToLabel), 2, 1, Qt::AlignBottom);
    q->addWidget(_moveToList, 3, 1, Qt::AlignTop);

    int submitLocation = 4;
    int cancelLocation = 5;
    if (_displayAddRemove)
    {
        _addPatientButton = new QPushButton("Add Patient");
        _removePatientButton = new QPushButton("Remove Patient");
        q->addWidget(_addPatientButton, 4, 1, Qt::AlignTop);
        q->addWidget(_removePatientButton, 5, 1, Qt::AlignTop);
        submitLocation = 6;
        cancelLocation = 7;
    }

    q->addWidget(_submitButton, submitLocation, 1);
    q->addWidget(_cancelButton, cancelLocation, 1);
    setLayout(q);
}

void MovePatientForm::_setupConnections()
{
    connect(_patientList, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(_patientItemSelected(QTreeWidgetItem*)));
    connect(_moveToList, SIGNAL(currentIndexChanged(QString)), SLOT(_moveToChanged(QString)));
    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitButtonClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelButtonClicked()));

    if (_displayAddRemove)
    {
        connect(_addPatientButton, SIGNAL(clicked()), SLOT(_addPatientClicked()));
        connect(_removePatientButton, SIGNAL(clicked()), SLOT(_removePatientClicked()));
    }
}

/************** PRIVATE SLOTS ***************/
void MovePatientForm::_moveToChanged(QString moveTo)
{
    emit patientMoved(moveTo);
}

void MovePatientForm::_patientItemSelected(QTreeWidgetItem* item)
{
    if (item) { emit patientSelected(item->text(1)); }
}

void MovePatientForm::_addPatientClicked()
{
    emit addPatientClicked();
}

void MovePatientForm::_removePatientClicked()
{
    emit removePatientClicked();
}

void MovePatientForm::_submitButtonClicked()
{
    emit submitButtonClicked();
}

void MovePatientForm::_cancelButtonClicked()
{
    emit cancelButtonClicked();
}

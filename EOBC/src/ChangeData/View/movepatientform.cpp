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
MovePatientForm::MovePatientForm(QString title, bool displayBedType, QString moveTo, QWidget *parent) :
    QWidget(parent), _displayBedType(displayBedType), _moveToLabel(moveTo)
{
    setWindowTitle(title);

    int width = 520;
    int height = 300;

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
 * @todo fix this to include columns
 */
void MovePatientForm::setPatientItems(QStringList& items)
{
    _patientList->clear();
    if (items.size() > 0)
    {
        _patientList->addItems(items);
        _patientList->item(0)->setSelected(true);
        _moveToList->setEnabled(true);
    }
    else
    {
        _moveToList->setEnabled(false);
    }
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
   return _patientList->currentRow();
}

QString MovePatientForm::getCurrentPatient()
{
    return _patientList->currentItem()->text();
}

void MovePatientForm::setCurrentMoveToItem(int index)
{
    _moveToList->setCurrentIndex(index);
}

void MovePatientForm::_setupLayout()
{
    _patientList    = new QListWidget();
    _facilityList   = new QComboBox();
    _moveToList     = new QComboBox();

    _patientList->setSelectionMode(QAbstractItemView::SingleSelection);

    _moveToList->setEnabled(false);

    _submitButton   = new QPushButton("Submit");
    _cancelButton   = new QPushButton("Cancel");

    _submitButton->setMinimumWidth(125);
    _cancelButton->setMinimumWidth(125);

    QGridLayout* q = new QGridLayout();
    q->setColumnMinimumWidth(1, 150);
    for (int i = 0; i < 3; ++i) { q->setRowStretch(i, 0); }
    for (int i = 3; i < 6; ++i) { q->setRowStretch(i,100); }
    q->addWidget(new QLabel("Patients"), 0, 0);
    q->addWidget(new QLabel("From Facility"), 0, 1);
    q->addWidget(_patientList, 1, 0, 5, 1);
    q->addWidget(_facilityList, 1, 1);
    q->addWidget(new QLabel(_moveToLabel), 2, 1, Qt::AlignBottom);
    q->addWidget(_moveToList, 3, 1, Qt::AlignTop);
    q->addWidget(_submitButton, 4, 1);
    q->addWidget(_cancelButton, 5, 1);
    setLayout(q);
}

void MovePatientForm::_setupConnections()
{
    connect(_patientList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), SLOT(_patientItemSelected(QListWidgetItem*)));
    connect(_moveToList, SIGNAL(currentIndexChanged(QString)), SLOT(_moveToChanged(QString)));
    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitButtonClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelButtonClicked()));
}

/************** PRIVATE SLOTS ***************/
void MovePatientForm::_moveToChanged(QString moveTo)
{
    emit patientMoved(moveTo);
}

void MovePatientForm::_patientItemSelected(QListWidgetItem* item)
{
    emit patientSelected(item->text());
}

void MovePatientForm::_submitButtonClicked()
{
    emit submitButtonClicked();
}

void MovePatientForm::_cancelButtonClicked()
{
    emit cancelButtonClicked();
}

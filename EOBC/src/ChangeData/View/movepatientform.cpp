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
}

/**
 * Set the items of the Facility combo box, removes the old ones
 *
 * @param items a list of values to insert into it
 */
void MovePatientForm::setFacilityItems(QStringList& items)
{
    _setComboboxItems(items, _facilityList);
}

/**
 * Set the items of the Move To combo box, removes the old ones
 *
 * @param items a list of values to insert into it
 */
void MovePatientForm::setMoveToItems(QStringList& items)
{
    _setComboboxItems(items, _moveToList);
}

/**
 * Private function to set the items of any combo box, removes the old ones
 *
 * @param items a list of values to insert into it
 */
void MovePatientForm::_setComboboxItems(QStringList &items, QComboBox *box)
{
    int num = box->count();
    if (num != 0)
    {
        // Remove all the items from the combo box
        for (int i = 0; i < num; ++i)
        {
            box->removeItem(0);
        }
    }
    box->insertItems(0, items);
}

void MovePatientForm::_setupLayout()
{
    _patientList    = new QListWidget();
    _facilityList   = new QComboBox();
    _moveToList     = new QComboBox();

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

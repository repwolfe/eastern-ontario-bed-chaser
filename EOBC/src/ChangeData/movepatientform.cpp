#include "movepatientform.h"
#include "../Common/convenience.h"

#include <QGridLayout>
#include <QLabel>

MovePatientForm::MovePatientForm(QString title, bool displayBedType, QString moveTo, QWidget *parent) :
    QWidget(parent), _displayBedType(displayBedType), _moveToLabel(moveTo)
{
    setWindowTitle(title);

    int width = 520;
    int height = 325;

    setGeometry(Convenience::getCenterForSize(width, height));

    _setupLayout();
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
    q->setRowStretch(0, 0);
    for (int i = 1; i < 6; ++i) {q->setRowStretch(i,100);}
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

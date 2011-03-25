#include "updatebedsform.h"
#include "convenience.h"

#include <QFormLayout>

UpdateBedsForm::UpdateBedsForm(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Update Beds");

    int width = 275;
    int height = 200;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);


    _setupLayout();
}

void UpdateBedsForm::_setupLayout()
{
    _ACBeds     = new QAbstractSpinBox();
    _CCCBeds    = new QAbstractSpinBox();
    _LTCBeds    = new QAbstractSpinBox();

    _facilities = new QComboBox();

    _submitButton = new QPushButton("Update");
    _cancelButton = new QPushButton("Cancel");

    _submitButton->setMaximumWidth(125);
    _cancelButton->setMaximumWidth(125);

    QFormLayout* q = new QFormLayout();
    q->addRow("Facility", _facilities);
    q->addRow("AC Beds", _ACBeds);
    q->addRow("CCC Beds", _CCCBeds);
    q->addRow("LTC Beds", _LTCBeds);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

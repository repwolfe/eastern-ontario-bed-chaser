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

void UpdateBedsForm::setNumAC(int num)
{
    _ACBeds->setValue(num);
}

void UpdateBedsForm::setNumCCC(int num)
{
    _CCCBeds->setValue(num);
}

void UpdateBedsForm::setNumLTC(int num)
{
    _LTCBeds->setValue(num);
}

void UpdateBedsForm::setMinimumAC(int num)
{
    _ACBeds->setMinimum(num);
}

void UpdateBedsForm::setMinimumCCC(int num)
{
    _CCCBeds->setMinimum(num);
}

void UpdateBedsForm::setMinimumLTC(int num)
{
    _LTCBeds->setMinimum(num);
}

int UpdateBedsForm::getNumAC() const
{
    return _ACBeds->value();
}

int UpdateBedsForm::getNumCCC() const
{
    return _CCCBeds->value();
}

int UpdateBedsForm::getNumLTC() const
{
    return _LTCBeds->value();
}

QString UpdateBedsForm::getCurrentFacility() const
{
    return _facilities->currentText();
}

void UpdateBedsForm::_submitClicked()
{
    emit submitClicked();
}

void UpdateBedsForm::_cancelClicked()
{
    close();
}

void UpdateBedsForm::_setupLayout()
{
    _ACBeds     = new QSpinBox();
    _CCCBeds    = new QSpinBox();
    _LTCBeds    = new QSpinBox();

    _facilities = new QComboBox();

    _submitButton = new QPushButton("Update");
    _cancelButton = new QPushButton("Cancel");

    _submitButton->setMaximumWidth(125);
    _cancelButton->setMaximumWidth(125);

    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelClicked()));

    QFormLayout* q = new QFormLayout();
    q->addRow("Facility", _facilities);
    q->addRow("AC Beds", _ACBeds);
    q->addRow("CCC Beds", _CCCBeds);
    q->addRow("LTC Beds", _LTCBeds);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

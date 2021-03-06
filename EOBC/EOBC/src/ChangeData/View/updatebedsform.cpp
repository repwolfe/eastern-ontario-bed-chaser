#include "updatebedsform.h"
#include "convenience.h"

#include <QFormLayout>

UpdateBedsForm::UpdateBedsForm(QWidget *parent) :
    QWidget(parent, Qt::WindowStaysOnTopHint)
{
    setWindowTitle("Update Beds");

    int width = 275;
    int height = 200;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);


    _setupLayout();
}

void UpdateBedsForm::setFacilityItems(QStringList& items)
{
    _facilities->clear();
    _facilities->insertItems(0, items);
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

void UpdateBedsForm::setMaximumAC(int num)
{
    _ACBeds->setMaximum(num);
}

void UpdateBedsForm::setMaximumCCC(int num)
{
    _CCCBeds->setMaximum(num);
}

void UpdateBedsForm::setMaximumLTC(int num)
{
    _LTCBeds->setMaximum(num);
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

int UpdateBedsForm::getCurrentFacilityIndex() const
{
    return _facilities->currentIndex();
}

void UpdateBedsForm::_submitClicked()
{
    emit submitClicked();
}

void UpdateBedsForm::_facilitySelected(int index)
{
    emit facilitySelected(index);
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

    const int maxBeds = 5000;
    _ACBeds->setMaximum(maxBeds);
    _CCCBeds->setMaximum(maxBeds);
    _LTCBeds->setMaximum(maxBeds);

    _facilities = new QComboBox();

    _submitButton = new QPushButton("Update");
    _cancelButton = new QPushButton("Cancel");

    _submitButton->setMaximumWidth(125);
    _cancelButton->setMaximumWidth(125);

    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelClicked()));
    connect(_facilities, SIGNAL(currentIndexChanged(int)), SLOT(_facilitySelected(int)));

    QFormLayout* q = new QFormLayout();
    q->addRow("Facility", _facilities);
    q->addRow("AC Beds", _ACBeds);
    q->addRow("CCC Beds", _CCCBeds);
    q->addRow("LTC Beds", _LTCBeds);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

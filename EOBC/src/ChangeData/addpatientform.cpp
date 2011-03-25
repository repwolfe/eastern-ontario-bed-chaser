#include "addpatientform.h"
#include "../Common/convenience.h"
#include <QFormLayout>

AddPatientForm::AddPatientForm(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Add Patient");

    int width = 300;
    int height = 275;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
}

void AddPatientForm::_setupLayout()
{
    _firstNameBox       = new QLineEdit();
    _lastNameBox        = new QLineEdit();
    _healthCardNumber   = new QLineEdit();
    _submitButton       = new QPushButton("Add Patient");
    _cancelButton       = new QPushButton("Cancel");

    _submitButton->setMaximumWidth(125);
    _cancelButton->setMaximumWidth(125);

    _requiredCareBox    = new QComboBox();
    _requiredCareBox->addItem("");
    _requiredCareBox->addItem("AC");
    _requiredCareBox->addItem("LTC");
    _requiredCareBox->addItem("CCC");

    QFormLayout* q = new QFormLayout();
    q->setContentsMargins(15, 10, 15, 10);
    q->setVerticalSpacing(20);
    q->addRow("First Name", _firstNameBox);
    q->addRow("Last Name", _lastNameBox);
    q->addRow("Health Card #", _healthCardNumber);
    q->addRow("Required Care", _requiredCareBox);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

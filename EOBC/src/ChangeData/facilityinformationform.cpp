#include "facilityinformationform.h"
#include "../Common/convenience.h"
#include <QFormLayout>

FacilityInformationForm::FacilityInformationForm(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Add Facility");

    int width = 250;
    int height = 240;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
}

void FacilityInformationForm::_setupLayout()
{
    _xAxisBox           = new QLineEdit();
    _yAxisBox           = new QLineEdit();
    _facilityNameBox    = new QLineEdit();

    _submitButton       = new QPushButton("Submit");
    _cancelButton       = new QPushButton("Cancel");

    _submitButton->setFixedWidth(125);
    _cancelButton->setFixedWidth(125);

    QFormLayout* q = new QFormLayout();
    q->setContentsMargins(15, 10, 15, 10);
    q->setVerticalSpacing(20);
    q->addRow("Name", _facilityNameBox);
    q->addRow("X-Axis", _xAxisBox);
    q->addRow("Y-Axis", _yAxisBox);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

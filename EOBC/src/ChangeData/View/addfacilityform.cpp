#include "addfacilityform.h"
#include "convenience.h"
#include <QFormLayout>

AddFacilityForm::AddFacilityForm(QWidget *parent) :
        QWidget(parent, Qt::WindowStaysOnTopHint)
{
    setWindowTitle("Add Facility");

    int width = 250;
    int height = 290;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
}

void AddFacilityForm::clearContents()
{
    _xAxisBox->clear();
    _yAxisBox->clear();
    _facilityNameBox->clear();
    _areas->setCurrentIndex(0);
    _errorMessage->setText("");
}

void AddFacilityForm::displayError()
{
    _errorMessage->setText("Incorrect values entered");
}

const QString AddFacilityForm::getXAxis() const
{
    return _xAxisBox->text();
}

const QString AddFacilityForm::getYAxis() const
{
    return _yAxisBox->text();
}

const QString AddFacilityForm::getFacilityName() const
{
    return _facilityNameBox->text();
}

int AddFacilityForm::getCurrentAreaIndex() const
{
    return _areas->currentIndex();
}

void AddFacilityForm::_submitClicked()
{
    emit submitClicked();
}

void AddFacilityForm::_cancelClicked()
{
    close();
    clearContents();
}

void AddFacilityForm::_setupLayout()
{
    _xAxisBox           = new QLineEdit();
    _yAxisBox           = new QLineEdit();
    _facilityNameBox    = new QLineEdit();
    _areas		= new QComboBox();

    _errorMessage	= new QLabel();
    _errorMessage->setStyleSheet("QLabel { color : red; }");

    _submitButton       = new QPushButton("Submit");
    _cancelButton       = new QPushButton("Cancel");

    _submitButton->setFixedWidth(125);
    _cancelButton->setFixedWidth(125);

    QStringList areas;
    for (int i = 0; i < Convenience::NUM_AREAS; ++i)
    {
	areas << Convenience::areaIDtoQString(i);
    }
    _areas->addItems(areas);

    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelClicked()));

    QFormLayout* q = new QFormLayout();
    q->setContentsMargins(15, 10, 15, 10);
    q->setVerticalSpacing(15);
    q->addRow("Name", _facilityNameBox);
    q->addRow("Area", _areas);
    q->addRow("X-Axis", _xAxisBox);
    q->addRow("Y-Axis", _yAxisBox);
    q->addRow(_errorMessage);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

#include "addpatientform.h"
#include "convenience.h"
#include <QFormLayout>

AddPatientForm::AddPatientForm(bool addingToBed, QWidget *parent) :
    QWidget(parent, Qt::WindowStaysOnTopHint), _addingToBed(addingToBed)
{
    setWindowTitle("Add Patient");

    int width = 300;
    int height = 320;

    if (addingToBed) { height += 30; }

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
}

AddPatientForm::~AddPatientForm()
{
    // This Widget wasn't added to a layout, have to delete it manually
    if (!_addingToBed)
    {
        delete _occuringCareBox;
    }
}

const QString AddPatientForm::getFirstName() const
{
    return _firstNameBox->text();
}

const QString AddPatientForm::getLastName() const
{
    return _lastNameBox->text();
}

const QString AddPatientForm::getHealthCardNumber() const
{
    return _healthCardNumber->text();
}

const QString AddPatientForm::getRequiredCare() const
{
    return _requiredCareBox->currentText();
}

const QString AddPatientForm::getOccuringCare() const
{
    return _occuringCareBox->currentText();
}

const QDate AddPatientForm::getDateAdded() const
{
    return _dateAdded->date();
}

void AddPatientForm::_submitClicked()
{
    emit submitClicked();
}

void AddPatientForm::_cancelClicked()
{
    close();
    clearContents();
}

void AddPatientForm::clearContents()
{
    _firstNameBox->clear();
    _lastNameBox->clear();
    _healthCardNumber->clear();
    _requiredCareBox->setCurrentIndex(0);
    _occuringCareBox->setCurrentIndex(0);
    _dateAdded->setDate(QDate::currentDate());
    _errorMessage->setText("");
}

void AddPatientForm::displayError()
{
    _errorMessage->setText("Incorrect values entered");
}

void AddPatientForm::_setupLayout()
{
    _firstNameBox       = new QLineEdit();
    _lastNameBox        = new QLineEdit();
    _healthCardNumber   = new QLineEdit();

    _errorMessage	= new QLabel();
    _errorMessage->setStyleSheet("QLabel { color : red; }");

    _submitButton       = new QPushButton("Add Patient");
    _cancelButton       = new QPushButton("Cancel");

    _submitButton->setMaximumWidth(125);
    _cancelButton->setMaximumWidth(125);

    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelClicked()));

    QStringList cares = QStringList() << "" << "AC" << "CCC" << "LTC";
    _requiredCareBox    = new QComboBox();
    _occuringCareBox    = new QComboBox();

    _requiredCareBox->addItems(cares);
    _occuringCareBox->addItems(cares);

    _dateAdded          = new QDateEdit();
    _dateAdded->setDisplayFormat("MMMM dd yyyy");
    _dateAdded->setDate(QDate::currentDate());
    _dateAdded->setDateRange(QDate(1900,1,1), QDate::currentDate());

    QFormLayout* q = new QFormLayout();
    q->setContentsMargins(15, 10, 15, 10);
    q->setVerticalSpacing(15);
    q->addRow("First Name", _firstNameBox);
    q->addRow("Last Name", _lastNameBox);
    q->addRow("Health Card #", _healthCardNumber);
    q->addRow("Required Care", _requiredCareBox);

    if (_addingToBed) { q->addRow("Occuring Care", _occuringCareBox); }

    q->addRow("Date Added", _dateAdded);
    q->addRow(_errorMessage);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

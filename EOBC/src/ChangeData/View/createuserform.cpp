#include "createuserform.h"
#include "convenience.h"
#include <QFormLayout>

CreateUserForm::CreateUserForm(QWidget *parent) :
    QWidget(parent, Qt::WindowStaysOnTopHint)
{
    setWindowTitle("Add User Account");

    int width = 300;
    int height = 245;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
}

void CreateUserForm::clearContents()
{
    _usernameBox->clear();
    _passwordBox->clear();
    _priveledgeMenu->setCurrentIndex(0);
}

const QString CreateUserForm::getUserName() const
{
    return _usernameBox->text();
}

const QString CreateUserForm::getPassword() const
{
    return _passwordBox->text();
}

const QString CreateUserForm::getPriveledge() const
{
    return _priveledgeMenu->currentText();
}

void CreateUserForm::_submitClicked()
{
    emit submitClicked();
}

void CreateUserForm::_cancelClicked()
{
    close();
    clearContents();
}

void CreateUserForm::_setupLayout()
{
    _usernameBox    = new QLineEdit();
    _passwordBox    = new QLineEdit();

    _priveledgeMenu = new QComboBox();
    _priveledgeMenu->addItem("System Administrator");
    _priveledgeMenu->addItem("LHIN Administrator");
    _priveledgeMenu->addItem("Facility Staff");

    _submitButton   = new QPushButton("Submit");
    _cancelButton   = new QPushButton("Cancel");

    connect(_submitButton, SIGNAL(clicked()), SLOT(_submitClicked()));
    connect(_cancelButton, SIGNAL(clicked()), SLOT(_cancelClicked()));

    _submitButton->setFixedWidth(125);
    _cancelButton->setFixedWidth(125);

    QFormLayout* q = new QFormLayout();
    q->setContentsMargins(15, 10, 15, 10);
    q->setVerticalSpacing(20);
    q->addRow("User Name", _usernameBox);
    q->addRow("Password", _passwordBox);
    q->addRow("Priveledge", _priveledgeMenu);
    q->addRow("", _submitButton);
    q->addRow("", _cancelButton);
    setLayout(q);
}

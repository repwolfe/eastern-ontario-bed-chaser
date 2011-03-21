#include "createuserform.h"
#include "../Common/convenience.h"
#include <QFormLayout>

CreateUserForm::CreateUserForm(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Add User Account");

    int width = 300;
    int height = 320;

    setGeometry(Convenience::getCenterForSize(width, height));
    setFixedSize(width, height);

    _setupLayout();
}

void CreateUserForm::_setupLayout()
{
    _usernameBox    = new QLineEdit();
    _passwordBox    = new QLineEdit();
    _firstNameBox   = new QLineEdit();
    _lastNameBox    = new QLineEdit();

    _priveledgeMenu = new QComboBox();
    _priveledgeMenu->addItem(tr("System Administrator"));
    _priveledgeMenu->addItem(tr("LHIN Administrator"));
    _priveledgeMenu->addItem(tr("Facility Staff"));

    _submitButton   = new QPushButton(tr("Submit"));
    _cancelButton   = new QPushButton(tr("Cancel"));

    _submitButton->setFixedWidth(125);
    _cancelButton->setFixedWidth(125);

    QFormLayout* q = new QFormLayout();
    q->setContentsMargins(15, 10, 15, 10);
    q->setVerticalSpacing(20);
    q->addRow(tr("User Name"), _usernameBox);
    q->addRow(tr("Password"), _passwordBox);
    q->addRow(tr("First Name"), _firstNameBox);
    q->addRow(tr("Last Name"), _lastNameBox);
    q->addRow(tr("&Priveledge"), _priveledgeMenu);
    q->addRow(tr(""), _submitButton);
    q->addRow(tr(""), _cancelButton);
    setLayout(q);
}

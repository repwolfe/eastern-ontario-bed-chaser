#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

/**
 * CreateUserForm is a form that appears and allows
 * the system administrator to create a new user at the
 * current Facility.
 *
 * This class is part of the ChangeData subsystem described in D2.
 */
class CreateUserForm : public QWidget
{
    Q_OBJECT
public:
    explicit CreateUserForm(QWidget *parent = 0);

signals:

public slots:

private:
    void _setupLayout();

    QLineEdit* _usernameBox;
    QLineEdit* _passwordBox;
    QLineEdit* _firstNameBox;
    QLineEdit* _lastNameBox;
    QComboBox* _priveledgeMenu;
    /// @todo Facility?
    QPushButton* _submitButton;
    QPushButton* _cancelButton;
};

#endif // CREATEUSERFORM_H

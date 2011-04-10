#ifndef CREATEUSERCONTROL_H
#define CREATEUSERCONTROL_H

#include <QObject>

#include "createuserform.h"

/**
 * @brief Controller for the CreateUserForm
 *
 * Displays the _form and handles submissions
 *
 * This class is part of the ChangeData subsystem described in D2
 */
class CreateUserControl : public QObject
{
    Q_OBJECT
public:
    CreateUserControl();
    ~CreateUserControl();

    void showForm();

signals:
    /// UserName, Password, Priveledge
    void submitClicked(QString, QString, QString);

private slots:
    void _submitClicked();

private:
    CreateUserForm* _form;

};

#endif // CREATEUSERCONTROL_H

#ifndef CREATEUSERCONTROL_H
#define CREATEUSERCONTROL_H

#include <QObject>

#include "createuserform.h"

/**
 * @brief Controller for the CreateUserForm
 *
 * Displays the form and handles submissions
 *
 * @todo traceability
 */
class CreateUserControl : public QObject
{
    Q_OBJECT
public:
    CreateUserControl();
    ~CreateUserControl();

    void showForm();

signals:
    /// UserName, Password, FirstName, LastName, Priveledge
    void submitClicked(QString, QString, QString, QString, QString);

private slots:
    void _submitClicked();

private:
    CreateUserForm *form;

};

#endif // CREATEUSERCONTROL_H

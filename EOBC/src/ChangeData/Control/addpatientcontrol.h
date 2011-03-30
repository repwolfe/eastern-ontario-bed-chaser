#ifndef ADDPATIENTCONTROL_H
#define ADDPATIENTCONTROL_H

#include <QObject>

#include "addpatientform.h"

/**
 * @brief Controller for AddPatientForm
 *
 * Displays the form and handles submissions
 *
 * @todo traceability
 */
class AddPatientControl : public QObject
{
    Q_OBJECT
public:
    AddPatientControl();
    ~AddPatientControl();

    void showForm();

signals:
    /// FirstName; LastName; HealthCardNum; RequiredCare
    void submitClicked(QString, QString, QString, QString);

private slots:
    void _submitClicked();

private:
    AddPatientForm* _form;

};

#endif // ADDPATIENTCONTROL_H

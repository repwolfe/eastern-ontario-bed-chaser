#ifndef ADDPATIENTCONTROL_H
#define ADDPATIENTCONTROL_H

#include <QObject>

#include "addpatientform.h"

/**
 * @brief Controller for AddPatientForm
 *
 * Displays the form and handles submissions
 *
 * This class is part of the ChangeData subsystem described in D2
 */
class AddPatientControl : public QObject
{
    Q_OBJECT
public:
    AddPatientControl(bool addingToBed);
    ~AddPatientControl();

    void showForm();

signals:
    /// FirstName; LastName; HealthCardNum; RequiredCare; DateAdded
    void submitClicked(QString, QString, QString, QString, QDate);

    /// FirstName; LastName; HealthCardNum; RequiredCare; DateAdded; OccuringCare
    void submitClicked(QString, QString, QString, QString, QDate, QString);

private slots:
    void _submitClicked();

private:
    AddPatientForm* _form;
    bool _addingToBed;

};

#endif // ADDPATIENTCONTROL_H

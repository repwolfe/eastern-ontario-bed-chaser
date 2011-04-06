#ifndef ADDFACILITYCONTROL_H
#define ADDFACILITYCONTROL_H

#include <QObject>

#include "addfacilityform.h"

/**
 * @brief Controller for AddFacilityForm
 *
 * Used to display the form
 * and handle submission
 *
 * This class is part of the ChangeData subsystem described in D2
 */
class AddFacilityControl : public QObject
{
    Q_OBJECT
public:
    AddFacilityControl();
    ~AddFacilityControl();

    void showForm();

signals:
    /// FacilityName; AreaId; X-Axis; Y-Axis
    void submitClicked(QString, ID, QString, QString);

private slots:
    void _submitClicked();

private:
    AddFacilityForm* _form;

};

#endif // ADDFACILITYCONTROL_H

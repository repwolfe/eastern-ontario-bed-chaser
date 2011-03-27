#ifndef ADDFACILITYCONTROL_H
#define ADDFACILITYCONTROL_H

#include <QObject>

#include "addfacilityform.h"

/**
 * @todo description
 * @todo traceability
 */
class AddFacilityControl : public QObject
{
    Q_OBJECT
public:
    AddFacilityControl();
    ~AddFacilityControl();

    void showForm();

signals:
    /// FacilityName; X-Axis; Y-Axis
    void submitClicked(QString, QString, QString);

private slots:
    void _submitClicked();

private:
    AddFacilityForm* form;

};

#endif // ADDFACILITYCONTROL_H

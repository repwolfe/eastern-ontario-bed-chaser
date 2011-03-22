#ifndef FACILITYINFORMATIONFORM_H
#define FACILITYINFORMATIONFORM_H

#include <QWidget>

/**
 * This class is a form which allows a system administrator
 * to create a new Facility.
 *
 * @todo check if only admin can do this
 * This class is part of the ChangeData subsystem described in D2.
 */
class FacilityInformationForm : public QWidget
{
    Q_OBJECT
public:
    explicit FacilityInformationForm(QWidget *parent = 0);

signals:

public slots:

private:


};

#endif // FACILITYINFORMATIONFORM_H

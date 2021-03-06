#ifndef UPDATEBEDSCONTROL_H
#define UPDATEBEDSCONTROL_H

#include <QObject>

#include "updatebedsform.h"
#include "facility.h"

/**
 * @brief Controller for UpdateBedsForm.
 *
 * Displays the form and handles submissions.
 *
 * This class is part of the ChangeData subsystem described in D2
 */
class UpdateBedsControl : public QObject
{
    Q_OBJECT
public:
    UpdateBedsControl();
    ~UpdateBedsControl();

    void waitingForData();
    void showForm();

    void setFacilitiesList(const QMap<ID, Facility*>& data);
    void setCurrentBedNumbers(const QMap<ID, QVector<int> >& data);
    void setMinimumBedNumbers(const QMap<ID, QVector<int> >& data);

signals:
    /// Facility*, Num AC Beds, Num CCC Beds, num LTC Beds
    void submitClicked(Facility*, int, int, int);

private slots:
    void _facilitySelected(int);
    void _submitClicked();

private:
    UpdateBedsForm* _form;
    QMap<int, Facility*> _indexToFacility;
    QMap<ID, QVector<int> > _currentBedNumbers;
    QMap<ID, QVector<int> > _minimumBedNumbers;

    bool _waitingForFacilitiesList;
    bool _waitingForMinBeds;
    bool _waitingForCurrentBeds;
};

#endif // UPDATEBEDSCONTROL_H

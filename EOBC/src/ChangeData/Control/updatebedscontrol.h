#ifndef UPDATEBEDSCONTROL_H
#define UPDATEBEDSCONTROL_H

#include <QObject>

#include "updatebedsform.h"
#include "patient.h"

/**
 * @brief Controller for UpdateBedsForm.
 *
 * Displays the form and handles submissions.
 *
 * @todo traceability
 */
class UpdateBedsControl : public QObject
{
    Q_OBJECT
public:
    UpdateBedsControl();
    ~UpdateBedsControl();

    void showForm();

    void setFacilitiesList(const QMap<ID, QString>& data);
    void setCurrentBedNumbers(const QMap<ID, QVector<int> >& data);
    void setMinimumBedNumbers(const QMap<ID, QVector<int> >& data);

signals:
    /// Facility Name, Num AC Beds, Num CCC Beds, num LTC Beds
    void submitClicked(QString, int, int, int);

private slots:
    void _submitClicked();

private:
    UpdateBedsForm* _form;


};

#endif // UPDATEBEDSCONTROL_H

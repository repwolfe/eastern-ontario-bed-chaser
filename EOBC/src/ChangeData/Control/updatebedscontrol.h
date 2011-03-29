#ifndef UPDATEBEDSCONTROL_H
#define UPDATEBEDSCONTROL_H

#include <QObject>

#include "updatebedsform.h"

/**
 * @todo description
 * @todo traceability
 */
class UpdateBedsControl : public QObject
{
    Q_OBJECT
public:
    UpdateBedsControl();
    ~UpdateBedsControl();

    void showForm();

signals:
    /// Facility Name, Num AC Beds, Num CCC Beds, num LTC Beds
    void submitClicked(QString, int, int, int);

private slots:
    void _submitClicked();

private:
    UpdateBedsForm* _form;


};

#endif // UPDATEBEDSCONTROL_H

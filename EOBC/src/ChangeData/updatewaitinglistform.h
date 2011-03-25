#ifndef UPDATEWAITINGLISTFORM_H
#define UPDATEWAITINGLISTFORM_H

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>

/**
 * A form that updates the waiting list of a particular
 * facility. You can add and remove patients from it
 * @todo Check if this is only LTC facilities
 *
 * This class is part of the ChangeData subsystem described in D2.
 */
class UpdateWaitingListForm : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateWaitingListForm(QWidget *parent = 0);

signals:

public slots:

private:
    void _setupLayout();

    QListWidget* _patientList;
    QComboBox* _facilityList;

    QPushButton* _addPatientButton;
    QPushButton* _removePatientButton;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;
};

#endif // UPDATEWAITINGLISTFORM_H

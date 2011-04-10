#ifndef UPDATEWAITINGLISTFORM_H
#define UPDATEWAITINGLISTFORM_H

#include <QWidget>
#include <QTreeWidget>
#include <QComboBox>
#include <QPushButton>
#include "QLinkedList"
#include "patient.h"

/**
 * @brief A form to Update the Waiting list of a Facility.
 *
 * A form that updates the waiting list of a particular
 * facility. You can add and remove patients from it
 *
 * This class is part of the ChangeData subsystem described in D2.
 */
class UpdateWaitingListForm : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateWaitingListForm(QWidget *parent = 0);

    bool getCurrentPatient(QString& outHcn) const;

    void addPatientItem(QString name, QString hcn);
    void removeSelectedPatientItem();

    bool isPatientInList(QString hcn) const;

    void setAreaItems(QStringList& items);
    void setPatientItems(const QLinkedList<Patient*>& inPatients);

signals:
    void addPatientClicked();
    void removePatientClicked();
    void submitClicked();
    void cancelClicked();
    void areaSelected(int);

private slots:
    void _submitClicked();
    void _cancelClicked();
    void _addPatientClicked();
    void _removePatientClicked();
    void _areaSelected(int);

private:
    void _setupLayout();
    void _setupConnections();

    QTreeWidget* _patientList;
    QComboBox*   _areaList;

    QPushButton* _addPatientButton;
    QPushButton* _removePatientButton;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;
};

#endif // UPDATEWAITINGLISTFORM_H

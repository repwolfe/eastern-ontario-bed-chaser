#ifndef UPDATEWAITINGLISTFORM_H
#define UPDATEWAITINGLISTFORM_H

#include <QWidget>
#include <QTreeWidget>
#include <QComboBox>
#include <QPushButton>

/**
 * @brief A form to Update the Waiting list of a Facility.
 *
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

    const QString getCurrentPatient() const;

    void addPatientItem(QString name, QString hcn);
    void removeSelectedPatientItem();

    bool isPatientInList(QString hcn) const;

    void setPatientItems(const QMap<QString,QString>& inPatients);

signals:
    void addPatientClicked();
    void removePatientClicked();
    void submitClicked();
    void cancelClicked();

private slots:
    void _submitClicked();
    void _cancelClicked();
    void _addPatientClicked();
    void _removePatientClicked();

private:
    void _setupLayout();
    void _setupConnections();

    QTreeWidget* _patientList;
    QComboBox* _facilityList;

    QPushButton* _addPatientButton;
    QPushButton* _removePatientButton;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;
};

#endif // UPDATEWAITINGLISTFORM_H

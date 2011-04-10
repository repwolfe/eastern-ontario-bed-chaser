#ifndef MOVEPATIENTFORM_H
#define MOVEPATIENTFORM_H

#include <QWidget>
#include <QTreeWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLinkedList>
#include <QMap>

#include "patient.h"

/**
 * @brief A form that Moves a patient.
 *
 * Has a drop down menu of all the facilities,
 * and depending on the selection populates a
 * list of all the admitted patients and optionally
 * what bed type they are in.
 * The form has a second drop down menu that will either
 * contain bed types or facilities, and this is what the
 * selected patient can be moved to.
 *
 * This class is part of the ChangeData subsystem described in D2
 */
class MovePatientForm : public QWidget
{
    Q_OBJECT
public:
   MovePatientForm(QString title, bool displayBedType, QString moveTo, bool displayAddRemove, QWidget *parent = 0);

   void setFacilityItems(QStringList& items);
   void setPatientItems(const QLinkedList<Patient*>& items, bool includeBeds = false);
   void setMoveToItems(QStringList& items);

   void removeFacilityItem(QString& item);

   void addPatientItem(QString name, QString hcn, QString bed=QString());
   void removeSelectedPatientItem();

   bool isPatientInList(QString hcn) const;

   int getCurrentPatientRow();
   bool getCurrentPatient(QString& outHcn) const;

   void setCurrentMoveToItem(int index);
   int getCurrentMoveToIndex() const;

signals:
   void patientMoved(QString moveTo);
   void patientMoved(int index);
   void patientSelected(QString patient);
   void addPatientClicked();
   void removePatientClicked();
   void submitButtonClicked();
   void cancelButtonClicked();
   void facilitySelected(int);

private slots:
   void _moveToChanged(QString moveTo);
   void _moveToChanged(int index);
   void _patientItemSelected(QTreeWidgetItem* item);
   void _addPatientClicked();
   void _removePatientClicked();
   void _submitButtonClicked();
   void _cancelButtonClicked();
   void _facilitySelected(int index);

private:
   void _setupLayout();
   void _setupConnections();
   void _setPatientItems(const QMap<QString,QString>& nameToHcn, const QMap<QString,QString>* hcnToBed = 0);

   bool _displayBedType;
   bool _displayAddRemove;

   QString _moveToLabel;

   QTreeWidget* _patientList;
   QComboBox* _facilityList;
   QComboBox* _moveToList;

   // Optional buttons
   QPushButton* _addPatientButton;
   QPushButton* _removePatientButton;

   // Mandatory buttons
   QPushButton* _submitButton;
   QPushButton* _cancelButton;
};

#endif // MOVEPATIENTFORM_H

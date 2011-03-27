#ifndef MOVEPATIENTFORM_H
#define MOVEPATIENTFORM_H

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMap>

/**
 * A form that Moves a patient.
 * Has a drop down menu of all the facilities,
 * and depending on the selection populates a
 * list of all the admitted patients and optionally
 * what bed type they are in.
 *
 * @todo Traceability/Add to D2
 */
class MovePatientForm : public QWidget
{
    Q_OBJECT
public:
   MovePatientForm(QString title, bool displayBedType, QString moveTo, QWidget *parent = 0);

   void setFacilityItems(QStringList& items);
   void setPatientItems(QStringList& items);
   void setMoveToItems(QStringList& items);

   void removeFacilityItem(QString& item);

   int getCurrentPatientRow();
   QString getCurrentPatient();

   void setCurrentMoveToItem(int index);

signals:
   void patientMoved(QString moveTo);
   void patientSelected(QString patient);
   void submitButtonClicked();
   void cancelButtonClicked();

private slots:
   void _moveToChanged(QString moveTo);
   void _patientItemSelected(QListWidgetItem* item);
   void _submitButtonClicked();
   void _cancelButtonClicked();

private:
   void _setupLayout();
   void _setupConnections();

   bool _displayBedType;
   QString _moveToLabel;

   QListWidget* _patientList;
   QComboBox* _facilityList;
   QComboBox* _moveToList;

   QPushButton* _submitButton;
   QPushButton* _cancelButton;
};

#endif // MOVEPATIENTFORM_H

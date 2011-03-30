#ifndef MOVEPATIENTFORM_H
#define MOVEPATIENTFORM_H

#include <QWidget>
#include <QTreeWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMap>

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
 * @todo Traceability/Add to D2
 */
class MovePatientForm : public QWidget
{
    Q_OBJECT
public:
   MovePatientForm(QString title, bool displayBedType, QString moveTo, QWidget *parent = 0);

   void setFacilityItems(QStringList& items);
   void setPatientItems(const QMap<QString,QString>& items);
   void setPatientItems(const QMap<QString,QString>& nameToHcn, const QMap<QString,QString>& hcnToBed);
   void setMoveToItems(QStringList& items);

   void removeFacilityItem(QString& item);

   void addPatientItem(QString name, QString hcn);
   void removeSelectedPatientItem();

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
   void _patientItemSelected(QTreeWidgetItem* item);
   void _submitButtonClicked();
   void _cancelButtonClicked();

private:
   void _setupLayout();
   void _setupConnections();
   void _setPatientItems(const QMap<QString,QString>& nameToHcn, const QMap<QString,QString>* hcnToBed = 0);

   bool _displayBedType;
   QString _moveToLabel;

   QTreeWidget* _patientList;
   QComboBox* _facilityList;
   QComboBox* _moveToList;

   QPushButton* _submitButton;
   QPushButton* _cancelButton;
};

#endif // MOVEPATIENTFORM_H

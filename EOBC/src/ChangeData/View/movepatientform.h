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
 //  const QString& getCurrentFacilitySelection() const;
 //  const QString& getCurrentMoveToSelection() const;


signals:


public slots:
   void patientMoved(QString moveTo);
   void patientSelected();

private:
   void _setupLayout();
   void _setupConnections();

   void _setComboboxItems(QStringList& items, QComboBox* box);

   bool _displayBedType;
   QString _moveToLabel;

   QListWidget* _patientList;
   QComboBox* _facilityList;
   QComboBox* _moveToList;

   QPushButton* _submitButton;
   QPushButton* _cancelButton;

   /// A Map of all the changes done to each Patient
   QMap<QString,QString> _moveToChanges;
};

#endif // MOVEPATIENTFORM_H

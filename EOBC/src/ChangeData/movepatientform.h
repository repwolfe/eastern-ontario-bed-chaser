#ifndef MOVEPATIENTFORM_H
#define MOVEPATIENTFORM_H

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>

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

signals:

public slots:

private:
   void _setupLayout();

   bool _displayBedType;
   QString _moveToLabel;

   QListWidget* _patientList;
   QComboBox* _facilityList;
   QComboBox* _moveToList;

   QPushButton* _submitButton;
   QPushButton* _cancelButton;
};

#endif // MOVEPATIENTFORM_H

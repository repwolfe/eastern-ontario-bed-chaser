#ifndef ADDFACILITYFORM_H
#define ADDFACILITYFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "convenience.h"

/**
 * @brief Form for adding a new Facility.
 *
 * This class is a form which allows a system administrator
 * to create a new Facility at a specific location with a name.
 *
 * @todo Rename this in D2 from FacilityInformationForm
 * //This class is part of the ChangeData subsystem described in D2.
 */
class AddFacilityForm : public QWidget
{
    Q_OBJECT
public:
    explicit AddFacilityForm(QWidget *parent = 0);

    void clearContents();
    void displayError();

    const QString getXAxis() const;
    const QString getYAxis() const;
    const QString getFacilityName() const;    
    int getCurrentAreaIndex() const;

signals:
    void submitClicked();

private slots:
    void _submitClicked();
    void _cancelClicked();

private:
    void _setupLayout();

    QLineEdit*	_xAxisBox;
    QLineEdit*	_yAxisBox;
    QLineEdit*	_facilityNameBox;
    QComboBox* _areas;
    QLabel*	_errorMessage;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;


};

#endif // ADDFACILITYFORM_H

#ifndef ADDFACILITYFORM_H
#define ADDFACILITYFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

/**
 * This class is a form which allows a system administrator
 * to create a new Facility.
 *
 * @todo Rename this in D2 from FacilityInformationForm
 * //This class is part of the ChangeData subsystem described in D2.
 */
class AddFacilityForm : public QWidget
{
    Q_OBJECT
public:
    explicit AddFacilityForm(QWidget *parent = 0);

signals:

public slots:

private:
    void _setupLayout();

    /// @todo What about Facility type? (Hospital/LTC)
    QLineEdit* _xAxisBox;
    QLineEdit* _yAxisBox;
    QLineEdit* _facilityNameBox;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;


};

#endif // ADDFACILITYFORM_H

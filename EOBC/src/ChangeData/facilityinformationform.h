#ifndef FACILITYINFORMATIONFORM_H
#define FACILITYINFORMATIONFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

/**
 * This class is a form which allows a system administrator
 * to create a new Facility.
 *
 * This class is part of the ChangeData subsystem described in D2.
 */
class FacilityInformationForm : public QWidget
{
    Q_OBJECT
public:
    explicit FacilityInformationForm(QWidget *parent = 0);

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

#endif // FACILITYINFORMATIONFORM_H

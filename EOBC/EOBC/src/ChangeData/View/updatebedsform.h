#ifndef UPDATEBEDSFORM_H
#define UPDATEBEDSFORM_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

/**
 * @brief Form to Update Beds
 *
 * A form that allows you to update the number of beds
 * of each type for a particular facility.
 *
 * This class is part of the ChangeData subsystem described in D2
 */
class UpdateBedsForm : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateBedsForm(QWidget *parent = 0);

    void setFacilityItems(QStringList& items);

    void setNumAC(int num);
    void setNumCCC(int num);
    void setNumLTC(int num);

    void setMinimumAC(int num);
    void setMinimumCCC(int num);
    void setMinimumLTC(int num);

    void setMaximumAC(int num);
    void setMaximumCCC(int num);
    void setMaximumLTC(int num);

    int getNumAC() const;
    int getNumCCC() const;
    int getNumLTC() const;
    int getCurrentFacilityIndex() const;

signals:
    void submitClicked();
    void facilitySelected(int);

private slots:
    void _submitClicked();
    void _cancelClicked();
    void _facilitySelected(int);

private:
    void _setupLayout();

    QSpinBox* _ACBeds;
    QSpinBox* _CCCBeds;
    QSpinBox* _LTCBeds;

    QComboBox* _facilities;

    QPushButton* _submitButton;
    QPushButton* _cancelButton;
};

#endif // UPDATEBEDSFORM_H

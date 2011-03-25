#ifndef ADDPATIENTFORM_H
#define ADDPATIENTFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

/**
 * This form allows you to add a patient to a waiting list or @todo facility??
 *
 * @todo Add this to D2
 */
class AddPatientForm : public QWidget
{
    Q_OBJECT
public:
    explicit AddPatientForm(QWidget *parent = 0);

signals:

public slots:

private:
    void _setupLayout();

    QLineEdit* _firstNameBox;
    QLineEdit* _lastNameBox;
    QLineEdit* _healthCardNumber;
    QComboBox* _requiredCareBox;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;

};

#endif // ADDPATIENTFORM_H

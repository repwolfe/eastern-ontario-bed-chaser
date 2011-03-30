#ifndef ADDPATIENTFORM_H
#define ADDPATIENTFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

/**
 * @brief Form to add a new Patient
 *
 * This form allows you to add a patient to a waiting list or @todo facility??
 *
 * @todo Add this to D2
 */
class AddPatientForm : public QWidget
{
    Q_OBJECT
public:
    explicit AddPatientForm(QWidget *parent = 0);

    void clearContents();

    void displayError();

    const QString getFirstName() const;
    const QString getLastName() const;
    const QString getHealthCardNumber() const;
    const QString getRequiredCare() const;

signals:
    void submitClicked();

private slots:
    void _submitClicked();
    void _cancelClicked();

private:
    void _setupLayout();

    QLineEdit* _firstNameBox;
    QLineEdit* _lastNameBox;
    QLineEdit* _healthCardNumber;
    QComboBox* _requiredCareBox;
    QLabel* _errorMessage;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;

};

#endif // ADDPATIENTFORM_H

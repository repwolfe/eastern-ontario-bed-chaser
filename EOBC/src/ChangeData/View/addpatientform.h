#ifndef ADDPATIENTFORM_H
#define ADDPATIENTFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDateEdit>

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
    explicit AddPatientForm(bool addingToBed, QWidget *parent = 0);
    ~AddPatientForm();

    void clearContents();

    void displayError();

    const QString getFirstName() const;
    const QString getLastName() const;
    const QString getHealthCardNumber() const;
    const QString getRequiredCare() const;
    const QString getOccuringCare() const;
    const QDate   getDateAdded() const;

signals:
    void submitClicked();

private slots:
    void _submitClicked();
    void _cancelClicked();

private:
    void _setupLayout();

    bool _addingToBed;

    QLineEdit* _firstNameBox;
    QLineEdit* _lastNameBox;
    QLineEdit* _healthCardNumber;
    QComboBox* _requiredCareBox;
    QComboBox* _occuringCareBox;
    QDateEdit* _dateAdded;
    QLabel* _errorMessage;
    QPushButton* _submitButton;
    QPushButton* _cancelButton;

};

#endif // ADDPATIENTFORM_H

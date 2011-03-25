#ifndef UPDATEBEDSFORM_H
#define UPDATEBEDSFORM_H

#include <QWidget>
#include <QAbstractSpinBox>
#include <QComboBox>
#include <QPushButton>

/**
 * A form that allows you to update the number of beds
 * of each type of a particular facility.
 *
 * @todo Add to D2
 */
class UpdateBedsForm : public QWidget
{
    Q_OBJECT
public:
    explicit UpdateBedsForm(QWidget *parent = 0);

signals:

public slots:

private:
    void _setupLayout();

    QAbstractSpinBox* _ACBeds;
    QAbstractSpinBox* _CCCBeds;
    /// @todo What to do about this
    QAbstractSpinBox* _LTCBeds;

    QComboBox* _facilities;

    QPushButton* _submitButton;
    QPushButton* _cancelButton;
};

#endif // UPDATEBEDSFORM_H

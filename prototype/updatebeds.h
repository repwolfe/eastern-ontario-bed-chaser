#ifndef UPDATEBEDS_H
#define UPDATEBEDS_H

#include <QDialog>

namespace Ui {
    class UpdateBeds;
}

class UpdateBeds : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateBeds(QWidget *parent = 0);
    ~UpdateBeds();

private slots:
    void closeSlot();

private:
    Ui::UpdateBeds *ui;
};

#endif // UPDATEBEDS_H

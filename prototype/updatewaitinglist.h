#ifndef UPDATEWAITINGLIST_H
#define UPDATEWAITINGLIST_H

#include <QDialog>

namespace Ui {
    class UpdateWaitingList;
}

class UpdateWaitingList : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateWaitingList(QWidget *parent = 0);
    ~UpdateWaitingList();

private slots:
    void closeButtonSlot();

private:
    Ui::UpdateWaitingList *ui;
};

#endif // UPDATEWAITINGLIST_H

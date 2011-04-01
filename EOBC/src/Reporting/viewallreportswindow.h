#ifndef VIEWALLREPORTSWINDOW_H
#define VIEWALLREPORTSWINDOW_H

#include <QWidget>
#include <QtGui>
#include "convenience.h"
#include "viewreportwindow.h"
#include "reportbars.h"
class ViewAllReportsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ViewAllReportsWindow(QWidget *parent = 0);
    ~ViewAllReportsWindow();
    void addItem(Report* r);
signals:
    void pressedSelect(int);
public slots:
    void pressedSelectSlot();
    void pressedCancelSlot();
private:
    ViewReportWindow* wind;
    QListWidget* reportsBox;

};

#endif // VIEWALLREPORTSWINDOW_H

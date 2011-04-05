#ifndef VIEWALLREPORTSWINDOW_H
#define VIEWALLREPORTSWINDOW_H

#include <QWidget>
#include <QtGui>
#include "convenience.h"
#include "viewreportwindow.h"
#include "reportbars.h"

/** @brief ViewAllReportsWindow is a simple class that just shows all the available reports to view
  * Has a couple buttons and a QListWidget that shows the reports
  * Stores nothing
  */

class ViewAllReportsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ViewAllReportsWindow(QWidget *parent = 0);
    void addItem(Report* r);
signals:
    void pressedSelect(int);
public slots:
    void pressedSelectSlot();
    void pressedCancelSlot();
private:
    //ViewReportWindow* wind;
    QListWidget* reportsBox;
};

#endif // VIEWALLREPORTSWINDOW_H

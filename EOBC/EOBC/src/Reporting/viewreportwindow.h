#ifndef VIEWREPORTWINDOW_H
#define VIEWREPORTWINDOW_H

#include <QWidget>
#include "report.h"
#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include "convenience.h"

class ViewReportWindow : public QWidget
{
    Q_OBJECT
    /** @brief a simple class that just asks the given report to draw itself
      * contains a pointer to a report object given in the constructor
      * has a paint event where the report is asked to draw itself
      */


public:
    explicit ViewReportWindow(Report* __report, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:

public slots:
private:
    QLabel* background;
    Report* __report;

};

#endif // VIEWREPORTWINDOW_H

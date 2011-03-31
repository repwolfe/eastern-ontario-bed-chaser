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
public:
    explicit ViewReportWindow(Report* __report, QWidget *parent = 0);
    ~ViewReportWindow();
    void paintEvent(QPaintEvent *);
signals:

public slots:
private:
    QLabel* background;
    Report* __report;

};

#endif // VIEWREPORTWINDOW_H

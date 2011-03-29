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
    explicit ViewReportWindow(Report* r, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:

public slots:
private:
    QLabel* background;
    Report* report;

};

#endif // VIEWREPORTWINDOW_H

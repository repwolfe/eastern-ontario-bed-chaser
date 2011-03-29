#ifndef VIEWALLREPORTSWINDOW_H
#define VIEWALLREPORTSWINDOW_H

#include <QWidget>
#include <QtGui>
#include "convenience.h"
#include "viewreportwindow.h"
class ViewAllReportsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ViewAllReportsWindow(QWidget *parent = 0);

signals:

public slots:
    void pressedSelectSlot();
private:
    ViewReportWindow* wind;

};

#endif // VIEWALLREPORTSWINDOW_H

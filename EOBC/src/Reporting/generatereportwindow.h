#ifndef GENERATEREPORTWINDOW_H
#define GENERATEREPORTWINDOW_H

#include <QWidget>
#include <QtGui/qgridlayout.h>
#include <QtGui>

class GenerateReportWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GenerateReportWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout layout;

};

#endif // GENERATEREPORTWINDOW_H

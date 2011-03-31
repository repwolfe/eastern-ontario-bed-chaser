#ifndef GENERATEREPORTWINDOW_H
#define GENERATEREPORTWINDOW_H

#include <QWidget>
#include <QtGui/qgridlayout.h>
#include <QtGui>
#include "report.h"
#include "reportbars.h"
#include <QtGui/QMessageBox>
class GenerateReportWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GenerateReportWindow(QWidget *parent = 0);

signals:
    void reportGenerated(Report*);
public slots:
    void pressedSubmit();
private:
    QGridLayout layout;
    QDateEdit* dateStartEntry;
    QDateEdit* dateEndEntry;

};

#endif // GENERATEREPORTWINDOW_H

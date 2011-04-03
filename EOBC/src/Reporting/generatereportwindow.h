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
    void updateFacilities(const QMap<ID,QString>* facils);
signals:
    ////FOR TESTING ONLY
    void reportGenerated(Report*);
    ////FOR TESTING ONLY
    void sendReportRequest(QDate, QDate, ID, QString);

public slots:
    void pressedSubmit();
    void pressedCancel();
private:

private:
    QGridLayout layout;
    QDateEdit* dateStartEntry;
    QDateEdit* dateEndEntry;
    QComboBox* facilities;
    const QMap<ID,QString>* __facils;
    QMap<int,ID>* facilToRows;
    QComboBox* constraints;

};

#endif // GENERATEREPORTWINDOW_H

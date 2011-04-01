#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QtGui/qpainter.h>
#include <QTime>
#include <QDate>
#include <reportbars.h>
#include "convenience.h"


class Report : public QObject
{
    Q_OBJECT
    enum {OCCUPANCYRATESNUMBER,OCCUPANCYRATESPERCENT};
    enum {DAY,MONTH,YEAR};
public:
    explicit Report(QString date,QDate startDate,QVector<ReportBars*>& bars,int facilityType,int dateType,QObject *parent = 0);
    ~Report();
    void draw(QPainter& g);
    QString getDate();

signals:

public slots:

private:
    void drawGrid(QPainter& g);
    void drawBars(QPainter& g);
private:
    QString date;
    QDate startDate;
    QString xAxis;
    QString yAxis;
    QVector<ReportBars*> bars;
    float maxHeight;
    int facilityType;
    int type;
    int dateType;

};

#endif // REPORT_H

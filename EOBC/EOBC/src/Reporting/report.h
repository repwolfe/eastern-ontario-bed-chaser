#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QtGui/qpainter.h>
#include <QTime>
#include <QDate>
#include <reportbars.h>
#include "convenience.h"

/** @brief Report is the actual report object. It can render a graph that displays info to the user
  * Report stores reportbars, facilities involved with the report, and the start and end dates of the report.
  * The draw method has most of the intelligence, since the report knows how to draw itself on any widget.
  */


class Report : public QObject
{
    Q_OBJECT
    enum {OCCUPANCYRATESNUMBER,OCCUPANCYRATESPERCENT};
    enum {DAY,MONTH,YEAR};
public:
    explicit Report(QString date,QDate startDate,QVector<ReportBars*>& bars,int facilityType,int dateType,QVector<QString>& facility,QObject *parent = 0);
    ~Report();
    void draw(QPainter& g);
    QString getDate();
    int getBarNum();
    int getFacilNum();
    void setWidth(int w);
    void setHeight(int h);

signals:

public slots:

private:
    void drawGrid(QPainter& g);
    void drawBars(QPainter& g);
    void drawLegend(QPainter& g);
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
    QVector<QString> facility;

};

#endif // REPORT_H

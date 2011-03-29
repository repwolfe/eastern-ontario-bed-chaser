#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QtGui/qpainter.h>
#include <QTime>
#include <QDate>
#include <reportbars.h>

class Report : public QObject
{
    Q_OBJECT
public:
    explicit Report(QString date,QVector<ReportBars*>& bars,QObject *parent = 0);
    void draw(QPainter& g);
    QString getDate();

signals:

public slots:

private:
    void drawGrid(QPainter& g);
    void drawBars(QPainter& g);
private:
    QString date;
    QString xAxis;
    QString yAxis;
    QVector<ReportBars*> bars;
    float maxHeight;

};

#endif // REPORT_H

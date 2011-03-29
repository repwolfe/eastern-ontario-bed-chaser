#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QtGui/qpainter.h>
#include <QTime>
#include <QDate>

class Report : public QObject
{
    Q_OBJECT
public:
    explicit Report(QVector<int> bars,QObject *parent = 0);
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
    QVector<int> bars;
    float maxHeight;

};

#endif // REPORT_H

#ifndef REPORTBARS_H
#define REPORTBARS_H

#include <QObject>
#include <QtGui/qpainter.h>
#include<QtGui/QLinearGradient>
class ReportBars : public QObject
{
    Q_OBJECT
public:
    explicit ReportBars(int* barHeights,QObject *parent = 0);
    void draw(QPainter& g,int threeDness);
    int getHeight();
    void setPosition(QPoint p);
    void setSize(QPoint s);

signals:

public slots:
private:
    QPoint position;
    QPoint size;
    int* barHeights;
    QColor* barColors;
    QLinearGradient rg;
    int totalHeight;

};

#endif // REPORTBARS_H

#ifndef REPORTBARS_H
#define REPORTBARS_H

#include <QObject>
#include <QtGui/qpainter.h>
#include<QtGui/QLinearGradient>
class ReportBars : public QObject
{

    Q_OBJECT
public:
    explicit ReportBars(int* barHeights,QString* bartypes, QObject *parent = 0);
    ~ReportBars();
    void draw(QPainter& g,int threeDness);
    int getHeight();
    void setPosition(QPoint p);
    void setSize(QPoint s);
    void setBarMax(int bm);
    int* getAllHeights();
    QColor* getAllColors();
    QString* getAllBarTypes();

signals:

public slots:
private:
    QPoint position;
    QPoint size;
    int* barHeights;
    QColor* barColors;
    QString* barTypes;
    QLinearGradient rg;
    int totalHeight;
    int barMax;

};

#endif // REPORTBARS_H

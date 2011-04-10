#ifndef REPORTBARS_H
#define REPORTBARS_H

#include <QObject>
#include <QtGui/qpainter.h>
#include<QtGui/QLinearGradient>

 /** @brief the ReportBars class is designed to store data and render individual bars on a graph.
   * contains a QVector for the bar data, and a position for where the bar should be rendered.
   * each bar is drawn to appear three dimensional, and is drawn with a gradient for classyness
   */


class ReportBars : public QObject
{

    Q_OBJECT
public:
    explicit ReportBars(QVector<int>& barHeights,QVector<QString>& bartypes, QObject *parent = 0);
    ~ReportBars();
    void draw(QPainter& g,int threeDness);
    int getHeight();
    void setPosition(QPoint p);
    void setSize(QPoint s);
    void setBarMax(int bm);
    QVector<int>& getAllHeights();
    QColor* getAllColors();
    QVector<QString>& getAllBarTypes();

signals:

public slots:
private:
    QPoint position;
    QPoint size;
    QVector<int> barHeights;
    QColor* barColors;
    QVector<QString> barTypes;
    QLinearGradient rg;
    int totalHeight;
    int barMax;

};

#endif // REPORTBARS_H

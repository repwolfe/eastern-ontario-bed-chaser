#include "report.h"
int height = 300;
int left = 120;
int width = 300;
int threeDness = 20;
Report::Report(QVector<int> bars, QObject *parent) :
    QObject(parent)
{
    this->bars = bars;
    date = ""+QDate::currentDate().toString("d MMM yyyy");

    maxHeight = 0;
    for(int i=0;i<bars.count();i++)
    {
        if(bars.at(i) > maxHeight)
            maxHeight = bars.at(i);
    }
}
void Report::draw(QPainter& g)
{
    g.setBrush(Qt::white);
    g.setPen(Qt::black);
    g.drawRect(0,0,500,500);
    g.drawText(175,20,"Report: " + date);
    drawGrid(g);
    drawBars(g);
}
void Report::drawGrid(QPainter& g)
{
    int bars = 6;
    g.setBrush(QColor(190,255,190));
    g.drawRect(left,50,width,height);

    g.drawLine(left,50,left+width,50);
    g.drawLine(left,50,left-threeDness,50+ threeDness);

    g.drawLine(left-threeDness,50 + threeDness,left-threeDness,50 + height+ threeDness);
    g.drawLine(left,50,left,50 + height);
    g.drawLine(left + width,50,left+width,50 + height);

    g.drawLine(left,50+height,left+width,50+height);
    g.drawLine(left,50+height,left-threeDness,50+height+ threeDness);

    for(int i=1;i<bars;i++)
    {
        int ratio = (height / bars)*i;
        g.drawLine(left,50 +ratio,left+width,50+ratio);
        g.drawLine(left,50+ratio,left-threeDness,50+ratio+ threeDness);
    }
    QPolygon bottom;
    bottom.push_back(QPoint(left - threeDness,height + 50 + threeDness));
    bottom.push_back(QPoint(left,height + 50));
    bottom.push_back(QPoint(left+width,height + 50));
    bottom.push_back(QPoint(left+width - threeDness,height + 50 + threeDness));
    g.setBrush(Qt::gray);
    g.drawPolygon(bottom,Qt::OddEvenFill);
}
void Report::drawBars(QPainter& g)
{
    for(int i=0;i<bars.count();i++)
    {
        float curBar = bars.at(i);
        int barLeft = left + i*width/bars.count() + 10;
        float barWidth = width/bars.count() - 20;
        g.setBrush(Qt::blue);
        g.drawRect(barLeft,(50+height)-(curBar/maxHeight)*height,barWidth,(curBar/maxHeight)*height);
    }
}

QString Report::getDate()
{
    return date;
}

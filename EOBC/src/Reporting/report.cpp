#include "report.h"
int height = 300;
int left = 120;
int width = 300;
int threeDness = 10;
Report::Report(QString date, QDate startDate,QVector<ReportBars*>& bars, QObject *parent) :
    QObject(parent)
{
    this->bars = bars;
    this->date = date;
    this->startDate = startDate;
    type = Report::OCCUPANCYRATESNUMBER;
    maxHeight = 0;
    for(int i=0;i<bars.count();i++)
    {
        if(bars.at(i)->getHeight() > maxHeight)
            maxHeight = bars.at(i)->getHeight();
    }
}
void Report::draw(QPainter& g)
{
    g.setBrush(Qt::white);
    g.setPen(Qt::black);
    g.drawRect(0,0,500,500);

    drawGrid(g);
    drawBars(g);
}
void Report::drawGrid(QPainter& g)
{
    int bars = 6;
    g.setBrush(QColor(190,210,255));
    g.drawRect(left,50,width,height);

    g.drawLine(left,50,left+width,50);
    g.drawLine(left,50,left-threeDness,50+ threeDness);

    g.drawLine(left-threeDness,50 + threeDness,left-threeDness,50 + height+ threeDness);
    g.drawLine(left,50,left,50 + height);
    g.drawLine(left + width,50,left+width,50 + height);

    g.drawLine(left,50+height,left+width,50+height);
    g.drawLine(left,50+height,left-threeDness,50+height+ threeDness);

    for(int i=0;i<=bars;i++)
    {
        int ratio = (height / bars)*i;
        g.drawLine(left,50 +ratio,left+width,50+ratio);
        g.drawLine(left,50+ratio,left-threeDness,50+ratio+ threeDness);
        g.setPen(Qt::black);
        g.drawText(left - 40,50 + ratio + 15,QString::number((int)maxHeight - (i*(int)maxHeight/bars)));
    }
    QPolygon bottom;
    bottom.push_back(QPoint(left - threeDness,height + 50 + threeDness));
    bottom.push_back(QPoint(left,height + 50));
    bottom.push_back(QPoint(left+width,height + 50));
    bottom.push_back(QPoint(left+width - threeDness,height + 50 + threeDness));
    g.setBrush(Qt::gray);
    g.drawPolygon(bottom,Qt::OddEvenFill);

    //
    // DRAW TITLES
    //

    QFont font = g.font();//save old font
    g.setBrush(Qt::black);

    g.setFont(QFont("Times New Roman",16,5));
    g.drawText(100,20,"Report: " + date);
    g.setFont(QFont("Arial",14,5));
    g.drawText(width/2+left-30, height+50+threeDness + 60,"Time");
    g.drawText(left-30, height+50+threeDness + 30,""+startDate.toString("MMM"));
    if(this->type == Report::OCCUPANCYRATESNUMBER)
    {
        g.save();
        g.setFont(QFont("Arial",14,5));
        g.translate(left-70,height/2+125);
        g.rotate(-90);
        g.drawText(0,0,"Occupancy Rates");
        g.restore();
    }
    g.setFont(font); // restore old font
}
void Report::drawBars(QPainter& g)
{
    for(int i=0;i<bars.count();i++)
    {
        ReportBars* curBar = bars.at(i);

        int barLeft = left + i*width/bars.count() + 10;
        float barWidth = width/bars.count() - 20;
        int barHeight = curBar->getHeight();
        curBar->setPosition(QPoint(barLeft,(50+height)-(barHeight/maxHeight)*height));
        curBar->setSize(QPoint(barWidth,(barHeight/maxHeight)*height));

        //g.setBrush(Qt::blue);
        //g.drawRect(barLeft,(50+height)-(curBar->getHeight()/maxHeight)*height,barWidth,(curBar->getHeight()/maxHeight)*height);
        curBar->draw(g,threeDness);
        g.setPen(Qt::black);
        g.drawText(left+i*(width/bars.count()) + 15, height+50+threeDness + 30,""+QString::number(startDate.day()+i));
    }
}

QString Report::getDate()
{
    return date;
}

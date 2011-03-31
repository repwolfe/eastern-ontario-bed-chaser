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
    type = Report::OCCUPANCYRATES;
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
    g.drawText(175,20,"Report: " + date);
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
    }//what happens when the facil are too close together
    //right now nothing, but i can write some collision code
    //itl be really innexpensive if i just add it into the slot that listens to see if a new facility has been added
    //i just dont know what to do WHEN i know they are colliding. i dont want to change the coords of the facility
    //one possible option is to NEVER make the pie charts for the colliding facilities to show
    //another is to have a temp position just so they draw far appart from each other
    //but the problem with that is that if you move the position to somewhere away from the origin, then it might collide
    //with another facility
    //could you merge?
            //possibly, that would be hard to code...
 //draw the selected one?   //g.drawText(left - 40,50 + ratio,QString::number(maxHeight - (i*maxHeight/(bars))));
    //so have the dots draw regardless of the zoom, but as soon as you select it it becomes a pie chart?
    //only if you can have more than 1 selected
    //oh yeah, i still have to work on selecting multiple facilities
    QPolygon bottom;
    bottom.push_back(QPoint(left - threeDness,height + 50 + threeDness));
    bottom.push_back(QPoint(left,height + 50));
    bottom.push_back(QPoint(left+width,height + 50));
    bottom.push_back(QPoint(left+width - threeDness,height + 50 + threeDness));
    g.setBrush(Qt::gray);
    g.drawPolygon(bottom,Qt::OddEvenFill);

    g.setBrush(Qt::black);
    g.drawText(width/2+left-30, height+50+threeDness + 60,"Time");
    g.drawText(left-30, height+50+threeDness + 30,""+startDate.toString("MMM"));
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
        g.setBrush(Qt::black);
        g.drawText(left+i*(width/bars.count()) + 15, height+50+threeDness + 30,""+QString::number(startDate.day()+i));
    }
}

QString Report::getDate()
{
    return date;
}

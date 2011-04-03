#include "report.h"
int height = 300;
int left = 120;
int width = 300;
int top = 70;
int threeDness = 10;
Report::Report(QString date, QDate startDate,QVector<ReportBars*>& bars,int facilityType, int dateType,QString facility,QObject *parent) :
    QObject(parent)
{
    this->bars = bars;
    this->date = date;
    this->dateType = dateType;
    this->facilityType = facilityType;
    this->startDate = startDate;
    this->facility = facility;
    type = Report::OCCUPANCYRATESNUMBER;
    maxHeight = 0;
    for(int i=0;i<bars.count();i++)
    {
        if(facilityType == Convenience::LONGTERMCARE)
        {
            bars.at(i)->setBarMax(2);
        }
        if(bars.at(i)->getHeight() > maxHeight)
            maxHeight = bars.at(i)->getHeight();
    }
}
Report::~Report()
{
    QVector<ReportBars*>::iterator iter = bars.begin();
    while(iter != bars.end())
    {
        delete *iter;
        iter++;
    }
}

void Report::draw(QPainter& g)
{
    g.setBrush(Qt::white);
    g.setPen(Qt::black);
    g.drawRect(0,0,width + 400,500);

    drawGrid(g);
    drawBars(g);
}
void Report::drawGrid(QPainter& g)
{
    int bars = 6;
    g.setBrush(QColor(190,210,255));
    g.drawRect(left,top,width,height);

    g.drawLine(left,top,left+width,top);
    g.drawLine(left,top,left-threeDness,top+ threeDness);

    g.drawLine(left-threeDness,top + threeDness,left-threeDness,top + height+ threeDness);
    g.drawLine(left,top,left,top + height);
    g.drawLine(left + width,top,left+width,top + height);

    g.drawLine(left,top+height,left+width,top+height);
    g.drawLine(left,top+height,left-threeDness,top+height+ threeDness);

    for(int i=0;i<=bars;i++)
    {
        int ratio = (height / bars)*i;
        g.drawLine(left,top +ratio,left+width,top+ratio);
        g.drawLine(left,top+ratio,left-threeDness,top+ratio+ threeDness);
        g.setPen(Qt::black);
        g.drawText(left - 40,top + ratio + 15,QString::number((int)maxHeight - (i*(int)maxHeight/bars)));
    }
    QPolygon bottom;
    bottom.push_back(QPoint(left - threeDness,height + top + threeDness));
    bottom.push_back(QPoint(left,height + top));
    bottom.push_back(QPoint(left+width,height + top));
    bottom.push_back(QPoint(left+width - threeDness,height + top + threeDness));
    g.setBrush(Qt::gray);
    g.drawPolygon(bottom,Qt::OddEvenFill);

    //
    ///Draw Legend
    //

    drawLegend(g);



    //
    // DRAW TITLES
    //

    QFont font = g.font();//save old font
    g.setBrush(Qt::black);

    g.setFont(QFont("Times New Roman",16,5));
    QFontMetrics qfm(QFont("Times New Roman",16,5));
    g.drawText((width+200)/2-qfm.width(date)/2,20,"Report: " + date);

    g.setFont(QFont("Arial",14,5));
    g.drawText(width/2+left-30, height+top+threeDness + 60,"Time");
    g.drawText(10,height+top+threeDness + 60,facility);
    if(dateType == Report::DAY)
        g.drawText(left-30, height+top+threeDness + 30,""+startDate.toString("MMM"));
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

    //
    // DRAW TITLES
    //
}
void Report::drawBars(QPainter& g)
{
    for(int i=0;i<bars.count();i++)
    {
        ReportBars* curBar = bars.at(i);

        int barLeft = left + i*width/bars.count() + 10;
        float barWidth = width/bars.count() - 20;
        int barHeight = curBar->getHeight();
        curBar->setPosition(QPoint(barLeft,(top+height)-(barHeight/maxHeight)*height));
        curBar->setSize(QPoint(barWidth,(barHeight/maxHeight)*height));

        //g.setBrush(Qt::blue);
        //g.drawRect(barLeft,(50+height)-(curBar->getHeight()/maxHeight)*height,barWidth,(curBar->getHeight()/maxHeight)*height);
        curBar->draw(g,threeDness);
        g.setPen(Qt::black);
        if(dateType == Report::DAY)
            g.drawText(left+i*(width/bars.count()) + 15, height+top+threeDness + 20,""+QString::number(startDate.day()+i));
        if(dateType == Report::MONTH)
            g.drawText(left+i*(width/bars.count()) + 15, height+top+threeDness + 20,""+startDate.addMonths(i).toString("MMM"));
        if(dateType == Report::YEAR)
            g.drawText(left+i*(width/bars.count()) + 15, height+top+threeDness + 20,""+QString::number(startDate.year()+i));
    }
}

QString Report::getDate()
{
    return date;
}
int Report::getBarNum()
{
    return bars.count();
}
void Report::setWidth(int w)
{
    width = w;
}

void Report::drawLegend(QPainter& g)
{
    g.setFont(QFont("Arial",12,5));
    g.drawText(20,45,"Legend: ");
    QLinearGradient rg;
    ReportBars* curBar = bars.at(0);
    for(int i=0;i<4;i++)
    {
        if(curBar->getAllHeights()[i]>0 && curBar->getAllHeights()[i] < 1000)
        {
            rg.setStart(QPoint (100 + i*80,40));
            rg.setFinalStop(QPoint(100 + i*80,70));

            rg.setColorAt(0,curBar->getAllColors()[i].lighter(70));
            rg.setColorAt(1,curBar->getAllColors()[i].lighter(150));
            //rg.setColorAt(0.5,barColors[1]);
            //rg.setColorAt(0.75,barColors[2]);
            g.setBrush(rg);

            if(i<2)
            {
                g.drawText(100 + 25 + 70*i,55,""+curBar->getAllBarTypes()[i]);
                g.drawRect(100 + i * 70,40,20,20);
            }
            else
            {
                g.drawText(50 + 25 + 110*i,55,""+curBar->getAllBarTypes()[i]);
                g.drawRect(50 + i * 110,40,20,20);
            }
        }
    }
}

#include "reportbars.h"

ReportBars::ReportBars(int* barHeights,QString* barTypes,QObject *parent) :
    QObject(parent)
{
    barMax = 4;
    barColors = new QColor[4];
    barColors[0] = Qt::blue;
    barColors[1] = Qt::red;
    barColors[2] = QColor(100,255,0);
    barColors[3] = QColor(0,255,100);

    this->barTypes = new QString[4];
    this->barTypes[0] = barTypes[0];
    this->barTypes[1] = barTypes[1];
    this->barTypes[2] = barTypes[2];
    this->barTypes[3] = barTypes[3];

    this->barHeights = new int[4];
    this->barHeights[0] = barHeights[0];
    this->barHeights[1] = barHeights[1];
    this->barHeights[2] = barHeights[2];
    this->barHeights[3] = barHeights[3];
    this->totalHeight=barHeights[0]+barHeights[1]+barHeights[2]+barHeights[3];
    barMax=0;
    for(int i=0;i<4;i++)
    {
        if(barHeights[i]>0)
            barMax++;
    }
    //QLinearGradient rg(
     //   position+size/2,
       // QPoint(position.x(),position.y()+size.y()/2));
}
ReportBars::~ReportBars()
{
    delete barHeights;
    delete barColors;
}

void ReportBars::draw(QPainter& g,int threeDness)
{
    rg.setStart(position+size/2);
    rg.setFinalStop(QPoint(position.x(),position.y()+size.y()/2));

    rg.setColorAt(0,barColors[barMax-1].lighter(70));
    rg.setColorAt(1,barColors[barMax-1].lighter(150));
    //rg.setColorAt(0.5,barColors[1]);
    //rg.setColorAt(0.75,barColors[2]);
    g.setBrush(rg);
    g.setPen(Qt::black);
    //g.drawRect(position.x()-threeDness,position.y()+threeDness,size.x(),size.y()); ///Draw Face
    rg.setColorAt(0,barColors[0].lighter(70));
    rg.setColorAt(1,barColors[0].lighter(150));
    g.setBrush(rg);
    QPolygon top;                                                                   ///Draw Top
    top.push_back(QPoint(position.x()-threeDness,position.y()+threeDness));
    top.push_back(QPoint(position.x(),position.y()));
    top.push_back(QPoint(position.x()+size.x(),position.y()));
    top.push_back(QPoint(position.x()+size.x()-threeDness,position.y()+threeDness));
    g.drawPolygon(top);

    float lastHeight = 0;
    for(int i=0;i<barMax;i++)
    {
        g.setPen(Qt::black);
        rg.setColorAt(0,barColors[i].lighter(70));
        rg.setColorAt(1,barColors[i].lighter(150));
        g.setBrush(rg);                                          ///Draw Side
        QPolygon side;
        side.push_back(QPoint(position.x()+size.x()-threeDness,position.y()+threeDness+ lastHeight));
        side.push_back(QPoint(position.x()+size.x(),position.y()+ lastHeight));
        side.push_back(QPoint(position.x()+size.x(),position.y()+ lastHeight +barHeights[i]*size.y()/totalHeight));
        side.push_back(QPoint(position.x()+size.x()-threeDness,position.y()+threeDness+ lastHeight +barHeights[i]*size.y()/totalHeight));
        g.drawPolygon(side);

        g.drawRect(position.x()-threeDness,position.y()+ threeDness + lastHeight,size.x(),barHeights[i]*size.y()/totalHeight); ///Draw Other Faces
        lastHeight += barHeights[i]*size.y()/totalHeight;
        g.setPen(Qt::white);
        g.drawText(position.x()+size.x()/2 - 15,position.y()+lastHeight,QString::number(barHeights[i]));
    }
}
int ReportBars::getHeight()
{
    return totalHeight;
}
int* ReportBars::getAllHeights()
{
    return barHeights;
}
QColor* ReportBars::getAllColors()
{
    return barColors;
}
QString* ReportBars::getAllBarTypes()
{
    return barTypes;
}

void ReportBars::setPosition(QPoint p)
{
    position = p;
}

void ReportBars::setSize(QPoint s)
{
    size = s;
}
void ReportBars::setBarMax(int bm)
{
    this->barMax = bm;
    totalHeight = 0;
    for(int i=0;i<barMax;i++)
        this->totalHeight+=barHeights[i];
}

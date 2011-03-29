#include "facilityicon.h"
#define ICONRADIUS 17
#define MAXPIEMODENUM 20
#define MAPMIDDLEX 500
#define MAPMIDDLEY 400
int FacilityIcon::iconNum = 0;

FacilityIcon::FacilityIcon(QPoint pos,QString name, QString area, QObject *parent) :
    MapItem(parent)
{
    position = pos;
    piePercent = new float[3];
    piePercent[0]=12 +rand()%50;
    piePercent[1] = 12 +rand()%50;
    piePercent[2] = 100-(piePercent[0]+piePercent[1]);
    pieColor = new QColor[3];
    pieColor[0] = Qt::red;
    pieColor[1]= Qt::green;
    pieColor[2] = Qt::blue;
    this->name = name;
    this->area = area;
    iconNum ++;
}
void FacilityIcon::draw(QPainter& g)
{
    MapItem::draw(g);
    g.setPen(Qt::black);
    g.setBrush(Qt::blue);
    //g.drawEllipse(realPosition + mapPos,ICONSIZE*scale,ICONSIZE*scale);
    if(iconNum < (scale) * MAXPIEMODENUM)
    {
        QRect rect(realPosition+mapPos-QPoint(ICONRADIUS,ICONRADIUS)*scale,realPosition + mapPos +QPoint(ICONRADIUS,ICONRADIUS)*scale);
        float lastRot=359*16;
        for(int i=0;i<3;i++)
        {
            if(!selected)
                g.setBrush(pieColor[i]);
            else
                g.setBrush(pieColor[i].lighter(150));
            g.drawPie(rect,lastRot-piePercent[i]*3.6*16, piePercent[i]*3.6*16);
            lastRot -= piePercent[i]*3.6*16;
        }
    }
    else
    {
        g.setBrush(QColor(255,255,255));
        g.drawEllipse(realPosition + mapPos, (int)(ICONRADIUS*scale/3),(int)(ICONRADIUS*scale/3));
    }
}
void FacilityIcon::update(QPoint mouse)
{
    MapItem::update(mouse);
}
void FacilityIcon::move(QPoint mPos)
{
    mapPos = mPos;
}
void FacilityIcon::resizePoints(QPoint mouse, float scale)
{
    MapItem::resizePoints(mouse,scale);
    if(idealScale < scale)
    {
        QPoint distance = ((realPosition+mapPos) - mouse);

        double trueLength = sqrt(pow(distance.x(), 2) + pow(distance.y(), 2));
        if(trueLength < ICONRADIUS)
        {
            //selected = true;
        }
    }
}
QPoint FacilityIcon::getPosition()
{
    return position + QPoint(MAPMIDDLEX,MAPMIDDLEY);
}

QString FacilityIcon::getArea()
{
    return area;
}
QString FacilityIcon::getName()
{
    return name;
}
float FacilityIcon::getLTC()
{
    return piePercent[0];
}

float FacilityIcon::getCCC()
{
   return piePercent[1];
}
float FacilityIcon::getAC()
{
   return piePercent[2];
}
bool FacilityIcon::checkSetSelected(QPoint mouse)
{
    QPoint distance = ((realPosition+mapPos) - mouse);
    selected = false;
    double trueLength = sqrt(pow(distance.x(), 2) + pow(distance.y(), 2));
    if(trueLength < ICONRADIUS)
    {
        selected = true;
        return true;
    }
    return false;
}

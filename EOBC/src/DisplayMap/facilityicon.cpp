#include "facilityicon.h"
#define ICONRADIUS 17
#define MAXPIEMODENUM 20
#define MAPMIDDLEX 500
#define MAPMIDDLEY 400
int FacilityIcon::iconNum = 0;

FacilityIcon::FacilityIcon(QPoint pos,QString name, QString area, int type,QObject *parent) :
    MapItem(parent)
{
    position = pos;
    this->type = type;
    piePercent = new float[4];
    pieColor = new QColor[4];
    collidedIcon = false;
    if(type == Convenience::HOSPITAL)
    {
        //piePercent[0]=12 +rand()%50;
        //piePercent[1] = 12 +rand()%50;
        //piePercent[2] = 7 + rand()%12;
        //piePercent[3] = 100-(piePercent[0]+piePercent[1]+piePercent[2]);
        pieColor[0] = Qt::red;
        pieColor[2]= QColor(100,255,0);
        pieColor[3]= QColor(0,255,100);
        pieColor[1] = Qt::blue;
    }
    else
    {
        //piePercent[0]=30 +rand()%50;
        //piePercent[1] = 100-(piePercent[0]);

        //pieColor[0] = QColor(255,100,50);
        //pieColor[1]= QColor(150,150,0);
        pieColor[0] = QColor(0,200,200);
        pieColor[1]= QColor(0,100,255);
        pieColor[2] = Qt::blue;
        pieColor[3] = Qt::blue;
    }
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
    if(iconNum < (scale) * MAXPIEMODENUM && (collidedIcon == false|| selected == true))
    {
        QRect rect(realPosition+mapPos-QPoint(ICONRADIUS,ICONRADIUS),realPosition + mapPos +QPoint(ICONRADIUS,ICONRADIUS));
        float lastRot=359*16;
        for(int i=0;i<4;i++)
        {
            if(!selected)
                g.setBrush(pieColor[i]);
            else
                g.setBrush(pieColor[i].lighter(150));
            g.drawPie(rect,lastRot-piePercent[i]*3.6*16, piePercent[i]*3.6*16);
            lastRot -= piePercent[i]*3.6*16;
        }
        QString iconText = "";
        if(type == Convenience::HOSPITAL)
        {
            iconText = "H";
        }
        if(type == Convenience::LONGTERMCARE)
        {
            iconText = "L";
        }
        g.setPen(QColor(100,100,100));
        g.setFont(QFont("Arial",18));
        QPoint letterPos(-5,4);
        g.drawText(realPosition.x()+mapPos.x()+letterPos.x()-2,realPosition.y()+mapPos.y()+letterPos.y() +2,iconText);
        g.setPen(Qt::white);
        g.setFont(QFont("Arial",13));
        g.drawText(realPosition.x()+mapPos.x()+letterPos.x(),realPosition.y()+mapPos.y()+letterPos.y(),iconText);
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
bool FacilityIcon::checkSetSelectedBox(QPoint start,QPoint end)
{
    QRect rect;
    start +=  -mapPos;
    end += -mapPos;
    if(start.x()<end.x())
    {
        rect.setLeft(start.x());
        rect.setRight(end.x());
    }
    else
    {
        rect.setLeft(end.x());
        rect.setRight(start.x());
    }
    if(start.y()<end.y())
    {
        rect.setTop(start.y());
        rect.setBottom(end.y());
    }
    else
    {
        rect.setTop(end.y());
        rect.setBottom(start.y());
    }
    selected = false;
    if(rect.contains(realPosition))
    {
        //if(realPosition.x()>start.x())
        //if(realPosition.y()>start.y())
          //  if(realPosition.x()<end.x())
            //    if(realPosition.y()<end.y())
              //  {
                    selected= true;
                    return true;
                //}
    }
    return false;
}
void FacilityIcon::makeCollisionIcons(FacilityIcon* f, QVector<FacilityIcon*> icons)
{
    for(int i=1;i<icons.count()-1;i++)
    {
        QPoint distance = f->getPosition() - icons.at(i)->getPosition();
        double trueLength = sqrt(pow(distance.x(), 2) + pow(distance.y(), 2));
        if(trueLength < ICONRADIUS*1.5)
        {
            f->setCollided(true);
            icons.at(i)->setCollided(true);
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
    return piePercent[1];
}
float FacilityIcon::getCCC()
{
   return round(piePercent[0]);
}
float FacilityIcon::getAC()
{
   return round(piePercent[1]);

}
int FacilityIcon::getType()
{
    return type;
}
float FacilityIcon::getLTCOpen()
{
    return (int)piePercent[0];
}

float FacilityIcon::getCCCOpen()
{
   return round(piePercent[2]);
}
float FacilityIcon::getACOpen()
{
   return round(piePercent[3]);
}
void FacilityIcon::setCollided(bool col)
{
    collidedIcon = col;
}
void FacilityIcon::setArea(QString area)
{
    this->area = area;
}
void FacilityIcon::setPercents(int* per)
{
    int max = 0;
    for(int i=0;i<4;i++)
    {
        piePercent[i]=per[i];
        max += per[i];
    }
    for(int i=0;i<4;i++)
    {
        piePercent[i] = piePercent[i]*100/max;
    }
}


#include "mapvectors.h"
#define MAPMIDDLEX 500
#define MAPMIDDLEY 400

MapVectors::MapVectors(QColor color,QObject* parent) : MapItem(parent)
{
    col = color;
    //clicked = false;

}
MapVectors::~MapVectors()
{
    delete mapPoints;
}
MapVectors::MapVectors(const MapVectors& map)
{
   // col = Qt::white;
}

QVector<QPoint>& MapVectors::getVectors()
{
    return *mapPoints;
}
void MapVectors::setVectors(QVector<QPoint>* ve)
{
    mapPoints = ve;
    poly= QPolygonF(*ve);
    int x = 0,y=0;
    int right=0,left=1000, top = 1000, bottom = 0;
    QVector<QPoint>::iterator iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
        if(iter->x()> right)
            right = iter->x();
        if(iter->x()< left)
            left = iter->x();
        if(iter->y()< top)
            top = iter->y();
        if(iter->y()> bottom)
            bottom = iter->y();
        iter++;
    }
    x=(right+left)/2;
    y=(bottom+top)/2;
    position = QPoint(x - MAPMIDDLEX,y- MAPMIDDLEY);
   iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
        iter->setX(iter->x()-MAPMIDDLEX);
        iter->setY(iter->y()-MAPMIDDLEY);
        iter++;
    }
    idealPosition.setX(position.x());
    idealPosition.setY(position.y());
    if(col == Qt::blue)
            position.setY(position.y()+50);
    update(middle);

}
void MapVectors::update(QPoint mouse)
{

   /* if(scale != idealScale)
    {
        float scalediff = (idealScale - scale)/7 + 1;
        scale *= scalediff;

        QPointF tempPos(position.x()-30,position.y()-30);
        tempPos.setX(tempPos.x()-middle.x());
        tempPos.setY(tempPos.y()-middle.y());
        tempPos *= scale;
        tempPos.setX(tempPos.x()+middle.x());
        tempPos.setY(tempPos.y()+middle.y());

        poly = QPolygon(*mapPoints);
        for(int i=0;i<poly.count();i++)
        {
            //poly.setPoint(i,poly.point(i)*scale);
            poly[i].setX(poly[i].x()*scale);
            poly[i].setY(poly[i].y()*scale);
            //QPointF::s
        }


        idealPosition.setX(-cos(angle)*2 + idealPosition.x());
        idealPosition.setY(-sin(angle)*2 + idealPosition.y());
        if(idealScale < scale)
            mouse = QPoint(middle.x()-90,middle.y()-30);
        poly.translate(QPointF(idealPosition.x(),idealPosition.y()));
     }*/
    MapItem::update(mouse);
    if(scale != idealScale)
       {

           poly = QPolygon(*mapPoints);
           for(int i=0;i<poly.count();i++)
           {
               //poly.setPoint(i,poly.point(i)*scale);
               poly[i].setX(poly[i].x()*scale - realPosition.x());
               poly[i].setY(poly[i].y()*scale - realPosition.y());
               //QPointF::s
           }

           poly.translate(realPosition);
        }
}
void MapVectors::resizePoints(QPoint mouse, float scale)
{
    MapItem::resizePoints(mouse,scale);
    if(idealScale < scale)
    {
        if(poly.containsPoint(mouse, Qt::OddEvenFill))
        {
            selected = true;
        }
    }
}
QColor MapVectors::getCol()
{
    if(!selected && !hovered)
        return col;
    else if(hovered)
        return col.lighter(75);
    else
        return col.lighter(50);
}
QPolygonF& MapVectors::getPoly()
{
    return poly;
}



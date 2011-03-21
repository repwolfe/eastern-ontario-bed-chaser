#include "mapvectors.h"
QPoint MapVectors::middle;
MapVectors::MapVectors( QColor color)
{

    col = color;
    //clicked = false;
    scale = 0.99;
    idealScale = 0.9;
    selected = false;
}


QVector<QPoint>& MapVectors::getVectors()
{
    return *mapPoints;
}
void MapVectors::setVectors(QVector<QPoint>* ve)
{
    mapPoints = ve;
    poly= QPolygonF(*ve);
    //int x=0,y=0;
    //QVector<QPoint>::iterator iter = mapPoints->begin();
   /* while(iter != mapPoints->end())
    {
        x+=iter->x();
        y+=iter->y();
        iter++;
    }
    x/= mapPoints->count();
    y/= mapPoints->count();*/
   // position = QPoint(x-1050,y);
   /* iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
        iter->setX(iter->x()-position.x());
        iter->setY(iter->y()-position.y());
        iter++;
    }*/
    //idealScale = 0.99;
    update(middle);
}
void MapVectors::update(QPoint mouse)
{
    selected = false;
    if(idealScale > scale)
    {
        if(poly.containsPoint(mouse, Qt::OddEvenFill))
        {
            selected = true;
        }
    }
    if(scale != idealScale)
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
        if(idealScale < scale)
            mouse = QPoint(middle.x()-90,middle.y()-30);
        poly.translate(QPointF(tempPos.x()-mouse.x()+middle.y(),tempPos.y()-mouse.y()+middle.y()));
     }
}
void MapVectors::resizePoints(QPoint mouse, float scale)
{
    idealScale *= scale;
}
QColor MapVectors::getCol()
{
    return col;
}
QPolygonF& MapVectors::getPoly()
{
    return poly;
}
void MapVectors::setMiddle(QPoint middle)

{
    MapVectors::middle = middle;
}

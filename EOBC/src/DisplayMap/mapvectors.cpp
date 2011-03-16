#include "mapvectors.h"

MapVectors::MapVectors(QColor color)
{

    col = color;
    clicked = false;
    scale = 1;
    idealScale = 1;
}


QVector<QPoint>& MapVectors::getVectors()
{
    return *mapPoints;
}
void MapVectors::setVectors(QVector<QPoint>* ve)
{
    mapPoints = ve;
    poly= QPolygonF(*ve);
    int x=0,y=0;
    QVector<QPoint>::iterator iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
        x+=iter->x();
        y+=iter->y();
        iter++;
    }
    x/= mapPoints->count();
    y/= mapPoints->count();
    position = QPoint(x,y);
    iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
        iter->setX(iter->x()-position.x());
        iter->setY(iter->y()-position.y());
        iter++;
    }
}
void MapVectors::update(QPoint mouse)
{
    if(scale != idealScale)
    {
        float scalediff = (idealScale - scale)/7 + 1;
        scale *= scalediff;

        QPointF tempPos(position.x(),position.y());
        tempPos.setX(tempPos.x()-mouse.x());
        tempPos.setY(tempPos.y()-mouse.y());
        tempPos *= scale;
        tempPos.setX(tempPos.x()+mouse.x());
        tempPos.setY(tempPos.y()+mouse.y());
        float xdiff = (tempPos.x() - position.x())/1.01 + position.x();
        float ydiff = (tempPos.y() - position.y())/1.01 + position.y();
        poly = QPolygonF(*mapPoints);
        for(int i=0;i<poly.count();i++)
        {
            //poly.setPoint(i,poly.point(i)*scale);
            poly[i].setX(poly[i].x()*scale);
            poly[i].setY(poly[i].y()*scale);
            //QPointF::s
        }

        poly.translate(QPointF(xdiff,ydiff));
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

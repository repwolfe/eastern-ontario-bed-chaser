#include "mapvectors.h"

MapVectors::MapVectors(QColor color)
{

    col = color;
    clicked = false;
    ratio = 1;
}


QVector<QPoint>& MapVectors::getVectors()
{
    return *mapPoints;
}
void MapVectors::setVectors(QVector<QPoint>* ve)
{
    mapPoints = ve;
    poly= QPolygon(*ve);
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
void MapVectors::update()
{

}
void MapVectors::resizePoints(QPoint mouse)
{
    //QVector<QPoint>::iterator iter = mapPoints->begin();
    ratio *= 1.1;
    QPoint tempPos(position.x(),position.y());
    tempPos.setX(tempPos.x()-mouse.x());
    tempPos.setY(tempPos.y()-mouse.y());
    tempPos *= ratio;
    tempPos.setX(tempPos.x()+mouse.x());
    tempPos.setY(tempPos.y()+mouse.y());

    poly = QPolygon(*mapPoints);
    for(int i=0;i<poly.count();i++)
    {
        poly.setPoint(i,poly.point(i)*ratio);
    }
//    poly.resize();
    poly.translate(tempPos);
    /*while(iter != mapPoints->end())
    {
       iter->setX(iter->x() * ratio);
       iter->setY(iter->y() * ratio);
       iter->setX(iter->x()+position.x());
       iter->setY(iter->y()+position.y());
       iter++;
    }


    iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
       iter->setX(iter->x()-position.x());
       iter->setY(iter->y()-position.y());
       iter++;
    }
*/
   // poly = QPolygon(*mapPoints);
}
QColor MapVectors::getCol()
{
    return col;
}
QPolygon& MapVectors::getPoly()
{
    return poly;
}

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
    position = QPoint(x - middle.x(),y- middle.y());
   iter = mapPoints->begin();
    while(iter != mapPoints->end())
    {
        iter->setX(iter->x()-middle.x());
        iter->setY(iter->y()-middle.y());
        iter++;
    }
    idealPosition.setX(position.x());
    idealPosition.setY(position.y());
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
    if(scale != idealScale)
       {
           float scalediff = (idealScale - scale)/7 + 1;
           scale *= scalediff;

           QPointF tempPos(position.x()-30,position.y()-30);
           tempPos *= scale;

           poly = QPolygon(*mapPoints);
           for(int i=0;i<poly.count();i++)
           {
               //poly.setPoint(i,poly.point(i)*scale);
               poly[i].setX(poly[i].x()*scale - tempPos.x());
               poly[i].setY(poly[i].y()*scale - tempPos.y());
               //QPointF::s
           }
           realPosition = QPoint(tempPos.x(),tempPos.y());
           poly.translate(realPosition);
        }
}
void MapVectors::resizePoints(QPoint mouse, float scale)
{
    idealScale *= scale;
    selected = false;
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
    if(!selected)
    return col;
    else
        return col.lighter(50);
}
QPolygonF& MapVectors::getPoly()
{
    return poly;
}
void MapVectors::setMiddle(QPoint& middle)

{
    MapVectors::middle = middle;
}
bool MapVectors::isSelected()
{
    return selected;
}
QPoint MapVectors::getPosition()
{
    return position;
}
float MapVectors::getScale()
{
    return this->scale;
}
QPoint MapVectors::getRealPosition()
{
    return realPosition;
}

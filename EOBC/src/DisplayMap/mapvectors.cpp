#include "mapvectors.h"

MapVectors::MapVectors(QColor color)
{
    //setAttribute(Qt::WA_StaticContents);
    //resize(1000,600);
    //image = new QImage(1000,600, QImage::Format_ARGB32_Premultiplied);
    col = color;
}


QVector<QPoint>& MapVectors::getVectors()
{
    return *mapPoints;
}
void MapVectors::setVectors(QVector<QPoint>* ve)
{
    mapPoints = ve;
    //update();
}
void MapVectors::update()
{
   // repaint(0,0,1000,600);
}
void MapVectors::resizePoints()
{
    for(int i=0;i<mapPoints->count();i++)
    {
       // mapPoints->at(i).setX(2);
        mapPoints->at(i).isNull();
    }
}
QColor MapVectors::getCol()
{
    return col;
}

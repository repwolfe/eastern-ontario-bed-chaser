#include "maparea.h"

MapArea::MapArea(QVector<QPoint>* points,QColor color,QObject *parent) :
    QObject(parent)
{

    vec = new MapVectors(color);
    vec->setVectors(points);
    col = color;


}
MapArea::~MapArea()
{
    delete vec;
}
MapVectors* MapArea::getVec()
{
    return vec;
}
void MapArea::resize()
{
    vec->resizePoints();
}

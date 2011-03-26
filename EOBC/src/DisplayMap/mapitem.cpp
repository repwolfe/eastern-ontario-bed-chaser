#include "mapitem.h"
QPoint MapItem::middle;
MapItem::MapItem(QObject *parent) :
    QObject(parent)
{
    scale = 0.99;
    idealScale = 0.9;
    selected = false;
    hovered = false;
}
MapItem::~MapItem()
{

}
void MapItem::draw(QPainter& g)
{
    g;
}

void MapItem::update(QPoint mouse)
{
    mouse;

    if(scale != idealScale)
       {
           float scalediff = (idealScale - scale)/7 + 1;
           scale *= scalediff;

           QPointF tempPos(position.x(),position.y());
           tempPos *= scale;
           realPosition = QPoint(tempPos.x(),tempPos.y());
        }
}
void MapItem::resizePoints(QPoint mouse, float scale)
{
    idealScale *= scale;
    selected = false;
    mouse;
    if(idealScale < scale)
    {
       /* if(poly.containsPoint(mouse, Qt::OddEvenFill))
        {
            selected = true;
        }*/
    }
}
void MapItem::setMiddle(QPoint& middle)
{
    MapItem::middle = middle;
}
bool MapItem::isSelected()
{
    return selected;
}
QPoint MapItem::getPosition()
{
    return position;
}
float MapItem::getScale()
{
    return this->scale;
}
QPoint MapItem::getRealPosition()
{
    return realPosition;
}
void MapItem::setHovered(bool h)
{
    hovered = h;
}


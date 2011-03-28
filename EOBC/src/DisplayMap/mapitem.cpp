#include "mapitem.h"
QPoint MapItem::middle;
MapItem::MapItem(QObject *parent) :
    QObject(parent)
{
    scale = 0.99;
    idealScale = 0.8;
    selected = false;
    hovered = false;
}
MapItem::~MapItem()
{

}
MapItem::MapItem(const MapItem& ) : QObject()
{

}

void MapItem::draw(QPainter& )
{

}

void MapItem::update(QPoint )
{
   if(scale != idealScale)
   {
       float scalediff = (idealScale - scale)/7 + 1;
       scale *= scalediff;

       QPointF tempPos(position.x(),position.y());
       tempPos *= scale;
       realPosition = QPoint(tempPos.x(),tempPos.y());
    }
}
void MapItem::resizePoints(QPoint , float scale)
{
    idealScale *= scale;
    selected = false;
}
void MapItem::checkSetSelected(QPoint )
{

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


#include "facilityicon.h"
#define ICONSIZE 17
FacilityIcon::FacilityIcon(QPoint pos, QObject *parent) :
    MapItem(parent)
{
    position = pos;
}
void FacilityIcon::draw(QPainter& g)
{
    MapItem::draw(g);
    g.setPen(Qt::black);
    g.setBrush(Qt::blue);
    //g.drawEllipse(realPosition + mapPos,ICONSIZE*scale,ICONSIZE*scale);
    int rot = 359;
    g.drawPie(QRect(realPosition+mapPos,realPosition + mapPos +QPoint(ICONSIZE,ICONSIZE)*scale),(rot-120)*16, 120*16);
    rot -= 120;
    g.setBrush(Qt::green);
    g.drawPie(QRect(realPosition+mapPos,realPosition + mapPos +QPoint(ICONSIZE,ICONSIZE)*scale),(rot-120)*16, 120*16);
    rot -= 120;
    g.setBrush(Qt::red);
    g.drawPie(QRect(realPosition+mapPos,realPosition + mapPos +QPoint(ICONSIZE,ICONSIZE)*scale),(rot-120)*16, 120*16);
}
void FacilityIcon::update(QPoint mouse)
{
    MapItem::update(mouse);
}
void FacilityIcon::move(QPoint mPos)
{
    mapPos = mPos;
}

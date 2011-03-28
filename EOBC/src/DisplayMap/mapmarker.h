#ifndef MAPMARKER_H
#define MAPMARKER_H
#include "mapitem.h"

class MapMarker : public MapItem
{
public:
    MapMarker(QPoint pos,QObject* parent = 0);
    void draw(QPainter& g);
    void update(QPoint mouse);
    void move(QPoint mPos);
    void resizePoints(QPoint mouse, float scale);
    void setPosition(QPoint mouse);

private:
    QPoint mapPos;
};

#endif // MAPMARKER_H

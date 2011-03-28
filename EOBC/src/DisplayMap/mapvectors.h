#ifndef MAPVECTORS_H
#define MAPVECTORS_H

#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QPainter>
#include <qmath.h>
#include "mapitem.h"

/**
  * This class is designed to hold variables about each individual reigon of the map.
  * It has a polygon that is drawn on the screen, and a list of all the points in the polygon.
  * It has the functionality to scale each reigon, and reposition it based on the origin.
  *
  * This class fills the requirements listed by users being able to select reigons
  */

class MapVectors : public MapItem
{

public:
    MapVectors(QColor col, QObject* parent = 0);
    ~MapVectors();
    void update(QPoint mouse);
    void resizePoints(QPoint mouse, float scale);

    //QPoint getRealPosition();
    //bool isSelected();
    //QPoint getPosition();
    //float getScale();
    QPolygonF& getPoly();
    QColor getCol();
    QVector<QPoint>& getVectors();
    //void setHovered(bool);
    void setVectors(QVector<QPoint>* ve);
    static bool checkZoomOut(QVector<MapVectors*> vecs, QPoint mouse);
    void checkSetSelected(QPoint);
private:


signals:

public slots:

protected:


private:
    QVector<QPoint>* mapPoints;
    QPolygonF poly;
    //QPoint position;
    //QPoint realPosition;
    QColor col;
    //float scale;
    //float idealScale;
    //QPoint idealPosition;
    //bool selected;
    //bool hovered;
    //static QPoint middle;
};

#endif // MAPVECTORS_H

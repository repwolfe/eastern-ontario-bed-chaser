#ifndef MAPVECTORS_H
#define MAPVECTORS_H

#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QPainter>
class MapVectors
{

public:
    MapVectors(QColor col);
    QVector<QPoint>& getVectors();
    void setVectors(QVector<QPoint>* ve);
    void update(QPoint mouse);
    void resizePoints(QPoint mouse, float scale);
    QPolygonF& getPoly();
    QColor getCol();
signals:

public slots:

protected:
   /* void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);*/

private:
    QVector<QPoint>* mapPoints;
    QImage* image;
    QPolygonF poly;
    QPoint position;
    bool clicked;
    QColor col;
    float scale;
    float idealScale;
    QPoint idealPosition;
};

#endif // MAPVECTORS_H

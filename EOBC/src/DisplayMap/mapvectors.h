#ifndef MAPVECTORS_H
#define MAPVECTORS_H

#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QPainter>
#include <qmath.h>
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
    static void setMiddle(QPoint&);
    QPoint getRealPosition();
    bool isSelected();
    QPoint getPosition();
    float getScale();
signals:

public slots:

protected:


private:
    QVector<QPoint>* mapPoints;
    QImage* image;
    QPolygonF poly;
    QPoint position;
    QPoint realPosition;
    QColor col;
    float scale;
    float idealScale;
    QPoint idealPosition;
    bool selected;
    static QPoint middle;
};

#endif // MAPVECTORS_H

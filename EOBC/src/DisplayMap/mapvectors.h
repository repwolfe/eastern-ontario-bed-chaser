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
    ~MapVectors();
    void update(QPoint mouse);
    void resizePoints(QPoint mouse, float scale);

    static void setMiddle(QPoint&);
    QPoint getRealPosition();
    bool isSelected();
    QPoint getPosition();
    float getScale();
    QPolygonF& getPoly();
    QColor getCol();
    QVector<QPoint>& getVectors();
    void setHovered(bool);
    void setVectors(QVector<QPoint>* ve);
private:
    MapVectors(const MapVectors&);

signals:

public slots:

protected:


private:
    QVector<QPoint>* mapPoints;
    QPolygonF poly;
    QPoint position;
    QPoint realPosition;
    QColor col;
    float scale;
    float idealScale;
    QPoint idealPosition;
    bool selected;
    bool hovered;
    static QPoint middle;
};

#endif // MAPVECTORS_H

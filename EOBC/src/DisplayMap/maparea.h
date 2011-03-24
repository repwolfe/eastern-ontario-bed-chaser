#ifndef MAPAREA_H
#define MAPAREA_H

#include <QObject>
#include <QMainWindow>

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include "mapvectors.h"
#include "facilityicon.h"
class MapArea : public QWidget
{
    Q_OBJECT
public:
    MapArea(QObject *parent = 0);

    ~MapArea();
    QVector<MapVectors*>& getVecs();
    void addVecs(QVector<QPoint>* points, QColor col);
    void resize(QPoint p);
    static void setMiddle(QPoint& middle);

signals:

public slots:
    void timerEvent();
private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *);


private:
   QVector<MapVectors*> vecs;
   QVector<FacilityIcon*> icons;
   QTimer resizeTimer;
   QPoint lastMousePos;
   QPoint mapPos;
   bool zoomed;
   float zoomSpeed;
   static QPoint middle;
   void moveMap();
};

#endif // MAPAREA_H

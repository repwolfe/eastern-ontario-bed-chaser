#ifndef MAPAREA_H
#define MAPAREA_H

#include <QObject>
#include <QMainWindow>

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include "mapvectors.h"
#include "facilityicon.h"
#include "mapmarker.h"

/**
 * This class holds the widget in which the map is contained.
 * It also contains mapvectors which are a vector of areas put together,
 * and a vector of icons that represent facilities
 *
 * This class is part of the map requirements (i.e. FR.MAP.01)
 */

class MapArea : public QWidget
{
    Q_OBJECT
public:
    MapArea(QObject *parent = 0);

    ~MapArea();
    QVector<MapVectors*>& getVecs();
    void addVecs(QString reg,QVector<QPoint>* points, QColor col);
    void resize(QPoint p);
    static void setMiddle(QPoint& middle);
    void loadIcon();
    void loadLabels(QVector<QLabel*> labels);
    void startTimer();

signals:

public slots:
    void timerEvent();
private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void updateLabels();


private:
   QVector<MapVectors*> vecs;
   QVector<FacilityIcon*> icons;
   MapMarker* mapX;
   QTimer resizeTimer;
   QPoint lastMousePos;
   QPoint mapPos;
   bool zoomed;
   float zoomSpeed;
   static QPoint middle;
   void moveMap();
   QVector<QLabel*> labels;
};

#endif // MAPAREA_H

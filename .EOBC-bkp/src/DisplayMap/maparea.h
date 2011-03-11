#ifndef MAPAREA_H
#define MAPAREA_H

#include <QObject>
#include <QMainWindow>

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include "mapvectors.h"
class MapArea : public QObject
{
    Q_OBJECT
public:
    MapArea(QVector<QPoint>* points,QColor col,QObject *parent = 0);
    ~MapArea();
    MapVectors* getVec();
    void resize();

signals:

public slots:
private:
   MapVectors* vec;
   QColor col;

};

#endif // MAPAREA_H

#ifndef MAPAREA_H
#define MAPAREA_H

#include <QObject>
#include <QMainWindow>

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include "mapvectors.h"
class MapArea : public QWidget
{
    Q_OBJECT
public:
    MapArea(QColor col,QObject *parent = 0);

    ~MapArea();
    QVector<MapVectors*>& getVecs();
    void addVecs(QVector<QPoint>* points, QColor col);
    void resize();

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event);
private:
   QVector<MapVectors*> vecs;
   QColor col;

};

#endif // MAPAREA_H

#ifndef MAP_H
#define MAP_H

#include <QMainWindow>

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include "mapvectors.h"
#include <QtGui/QPushButton>
#include "maparea.h"
class Map : public QMainWindow
{
    Q_OBJECT
public:
    Map(QWidget *parent = 0);
    ~Map();

signals:

public slots:



private:
    QVector<QPoint>* loadFile(QString fname);
    void loadAreas();

private:
        QMenu* fileMenu;
        QAction* editAct;
        QLabel* mapLayout;
        QVector<MapArea*> areas;


};

#endif // MAP_H

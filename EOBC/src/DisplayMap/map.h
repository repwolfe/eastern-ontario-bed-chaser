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
    void clickSave();
    void clickOpen();

private:
    QVector<QPoint>* loadFile(QString fname);

private:

        QPushButton* butt;
        QPushButton* buttOpen;
        QLabel* mapLayout;
        QVector<MapArea*> areas;

       //void mouseMoveEvent(QMouseEvent *event);


};

#endif // MAP_H

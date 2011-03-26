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
#include "convenience.h"
class Map : public QMainWindow
{
    Q_OBJECT
public:
    Map(QWidget *parent = 0);
    ~Map();

signals:

public slots:


protected:
    void resizeEvent(QResizeEvent *);
private:
    QVector<QPoint>* loadFile(QString fname);
    void loadAreas();

private:
        QMenu* fileMenu;
        QAction* editAct;
        QLabel* mapLayout;
        QLabel* fName;
        QLabel* fArea;
        QLabel* fLTCRates;
        QLabel* fACRates;
        QLabel* fCCCRates;
        QLabel* fWList;
        QLabel* fCoord;
        MapArea* area;


};

#endif // MAP_H

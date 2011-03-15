#include "maparea.h"

MapArea::MapArea(QObject *parent) :
    QWidget() , vecs()
{
    //vecs = new QVector<MapVectors*>();
    //vec->setVectors(points);
   // col = color;
}
MapArea::~MapArea()
{
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        delete *iter;
        iter++;
    }
    vecs.clear();
}
QVector<MapVectors*>& MapArea::getVecs()
{
    return vecs;
}
void MapArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //Draw Background
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(0,0,1000,800));

    //Draw Polygons (areas)
    for(int i=0;i<this->vecs.count();i++)
    {
        painter.setPen(vecs.at(i)->getCol().darker());
        painter.setBrush(vecs.at(i)->getCol().lighter());
        painter.drawPolygon(vecs.at(i)->getPoly());

    }
}
void MapArea::addVecs(QVector<QPoint>* points, QColor col)
{

    QVector<QPoint>::iterator iter = points->begin();
    while(iter != points->end())
    {
        iter->setY(iter->y() - 10);
        iter++;
    }

    MapVectors* temp = new MapVectors(col);
    temp->setVectors(points);
    vecs.push_back(temp);
}

void MapArea::resize()
{
    //vec->resizePoints();
}
void MapArea::mousePressEvent(QMouseEvent *event)
{
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        (*iter)->resizePoints(QPoint(event->x(),event->y()));
        iter++;
    }
    repaint();
}

void MapArea::mouseReleaseEvent(QMouseEvent *event)
{

}

void MapArea::mouseClickEvent(QMouseEvent *event)
{

}

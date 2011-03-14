#include "maparea.h"

MapArea::MapArea(QColor color,QObject *parent) :
    QWidget() , vecs()
{
    //vecs = new QVector<MapVectors*>();
    //vec->setVectors(points);
    col = color;
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
   // painter.drawImage(QRect(0,-yoffset,1000,600+yoffset),mapPic,QRect(0,0,4200,2500));
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(0,0,1000,800));
    for(int i=0;i<this->vecs.count();i++)
    {
        //painter.drawLine(mapPoints->at(i),mapPoints->at(i+1));
        //painter.drawEllipse(mapPoints->at(i+1),5,5);
        painter.setPen(vecs.at(i)->getCol().darker());
        painter.setBrush(vecs.at(i)->getCol().lighter());
        painter.drawPolygon(QPolygon(vecs.at(i)->getVectors()));

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

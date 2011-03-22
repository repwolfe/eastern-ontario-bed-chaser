#include "maparea.h"

#define BASEZOOMSPEED 1.3
#define MOVESPEED 5
QPoint MapArea::middle;
MapArea::MapArea(QObject *parent) :
    QWidget() , vecs(), resizeTimer()
{
    zoomed = false;
   resizeTimer.start(10);
   connect(&resizeTimer,SIGNAL(timeout()),this,SLOT(timerEvent()));
   mapPos = QPoint(0,0);
   this->setMouseTracking(true);
   lastMousePos = middle;
   zoomSpeed = BASEZOOMSPEED;
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
    painter.drawRect(QRect(0,0,middle.x()*2,middle.y()*2));

    for(int i=0;i<this->vecs.count();i++)
    {
        painter.setPen(vecs.at(i)->getCol().darker());
        painter.setBrush(vecs.at(i)->getCol().lighter());
        painter.drawPolygon(vecs.at(i)->getPoly());
        //painter.drawEllipse(vecs.at(i)->getRealPosition() + mapPos,10,10);
    }
    //painter.drawEllipse(mapPos,15,15);
    //painter.drawEllipse(middle,10,10);
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
    temp->setMiddle(middle);
    vecs.push_back(temp);
    /*int x=0,y=0;
    iter = points->begin();
    while(iter != points->end())
    {
        x += iter->x();
        y += iter->y();
        iter++;
    }
    x /= points->size();
    y /= points->size();
    mapPos += QPoint(0,0)/vecs.size();*/
}
void MapArea::timerEvent()
{
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        (*iter)->update(lastMousePos);

        iter++;
    }
    moveMap();
    repaint();
}

void MapArea::resize(QPoint p)
{
    QVector<MapVectors*>::iterator iter = vecs.begin();
    float scale = 1;
    if(zoomed){
       // scale = 0.66;
        scale = 1/zoomSpeed;
        zoomed = false;
        lastMousePos = middle;
    }
    else
    {
        //scale = 1.5;
        scale = zoomSpeed;
        zoomed = true;
    }

    while(iter != vecs.end())
    {

         (*iter)->resizePoints(p,scale);
         iter++;
    }
    repaint();
}
void MapArea::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = QPoint(event->x(),event->y());
    resize(lastMousePos);

}

void MapArea::mouseReleaseEvent(QMouseEvent *event)
{

}

void MapArea::mouseClickEvent(QMouseEvent *event)
{

}
void MapArea::setMiddle(QPoint& middle)
{
    MapArea::middle = middle;

    MapVectors::setMiddle(middle);
}
void MapArea::moveMap()
{
    //mapPos = middle;
    QPoint middle(this->middle.x(),this->middle.y()+70);
    MapVectors* selectedArea = 0;
    for(int i=0;i<vecs.size();i++)
    {
        if(vecs[i]->isSelected())
        {
            selectedArea = vecs[i];
        }
    }
    if(selectedArea == 0)
    {
        if((middle-mapPos).manhattanLength() > MOVESPEED + 1)
        {
            float angle = atan2(middle.y()-mapPos.y(),middle.x() - mapPos.x());
            mapPos.setX(mapPos.x()+cos(angle)*MOVESPEED);
            mapPos.setY(mapPos.y()+sin(angle)*MOVESPEED);
        }
    }
    else
    {
        QPointF tempPos(selectedArea->getRealPosition().x(),selectedArea->getRealPosition().y());
       // tempPos *= selectedArea->getScale();
       tempPos += mapPos;

        if((tempPos-middle).manhattanLength() > MOVESPEED +1)
        {
            float angle = atan2(tempPos.y()-middle.y(),tempPos.x() - middle.x());
            mapPos.setX(mapPos.x()-cos(angle)*MOVESPEED);
            mapPos.setY(mapPos.y()-sin(angle)*MOVESPEED);
        }
    }
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        QPolygonF& p = (*iter)->getPoly();
        p.translate(mapPos);
        iter++;
    }
}
void MapArea::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mousePos(event->x(),event->y());
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        if((*iter)->getPoly().containsPoint(mousePos, Qt::OddEvenFill))
        {
            (*iter)->setHovered(true);
        }
        else
        {
            (*iter)->setHovered(false);
        }
        iter++;
    }
}

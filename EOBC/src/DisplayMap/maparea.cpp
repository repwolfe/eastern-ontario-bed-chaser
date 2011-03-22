#include "maparea.h"
#define MIDDLEX 470
#define MIDDLEY 400
QPoint MapArea::middle;
MapArea::MapArea(QObject *parent) :
    QWidget() , vecs(), resizeTimer()
{
    zoomed = false;
   resizeTimer.start(100);
   connect(&resizeTimer,SIGNAL(timeout()),this,SLOT(timerEvent()));
   mapPos = QPoint(MIDDLEX,MIDDLEY);
   lastMousePos = mapPos;
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
    temp->setMiddle(middle);
    vecs.push_back(temp);
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
        scale = 0.66;
        zoomed = false;
        lastMousePos = QPoint(MIDDLEX,MIDDLEY);
    }
    else
    {
        scale = 1.5;
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
        if((lastMousePos-mapPos).manhattanLength() > 3)
        {
            float angle = atan2(lastMousePos.y()-mapPos.y(),lastMousePos.x() - mapPos.x());
            mapPos.setX(mapPos.x()+cos(angle)*2);
            mapPos.setY(mapPos.y()+sin(angle)*2);
        }
    }
    else
    {
        QPointF tempPos(selectedArea->getRealPosition().x()-30,selectedArea->getRealPosition().y()-30);
       // tempPos *= selectedArea->getScale();
       tempPos += mapPos;

        if((tempPos-middle).manhattanLength() > 30)
        {
            float angle = atan2(tempPos.y()-middle.y(),tempPos.x() - middle.x());
            mapPos.setX(mapPos.x()-cos(angle)*20);
            mapPos.setY(mapPos.y()-sin(angle)*20);
        }
    }
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        (*iter)->getPoly().translate(mapPos);
        iter++;
    }
}

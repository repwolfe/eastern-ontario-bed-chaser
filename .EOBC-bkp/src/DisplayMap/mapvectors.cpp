#include "mapvectors.h"

MapVectors::MapVectors(QColor color,QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    resize(1000,600);
    image = new QImage(1000,600, QImage::Format_ARGB32_Premultiplied);
    col = color;


}
/*void MapVectors::mouseMoveEvent(QMouseEvent *event)
{

}
void MapVectors::mousePressEvent(QMouseEvent *event)
{
    this->mapPoints->push_back(QPoint(event->x(),event->y()));
    update();
}

void MapVectors::mouseReleaseEvent(QMouseEvent *event)
{

}
*/
void MapVectors::paintEvent(QPaintEvent *event)

{

    QPainter painter(this);
   // painter.drawImage(QRect(0,-yoffset,1000,600+yoffset),mapPic,QRect(0,0,4200,2500));
    painter.setPen(col.darker());
    painter.setBrush(col.lighter());
    for(int i=0;i<mapPoints->count()-1;i++)
    {
        painter.drawLine(mapPoints->at(i),mapPoints->at(i+1));
        //painter.drawEllipse(mapPoints->at(i+1),5,5);
        painter.drawPolygon(QPolygon(*mapPoints));

    }
}
QVector<QPoint>& MapVectors::getVectors()
{
    return *mapPoints;
}
void MapVectors::setVectors(QVector<QPoint>* ve)
{
    mapPoints = ve;
    //update();
}
void MapVectors::update()
{
    repaint(0,0,1000,600);
}
void MapVectors::resizePoints()
{
    for(int i=0;i<mapPoints->count();i++)
    {
       // mapPoints->at(i).setX(2);
        mapPoints->at(i).isNull();
    }
}

#include "maparea.h"

#define BASEZOOMSPEED 1.3
#define MOVESPEED 5
QPoint MapArea::middle;
#define MAPMIDDLEX 500
#define MAPMIDDLEY 400

/**
 * Constructor for MapArea. Generates the timer event for the map.
 *
 * @param parent not used
 */
MapArea::MapArea(QObject *parent) :
    QWidget() , vecs(), resizeTimer()
{
    zoomed = false;
   resizeTimer.start(10);
   connect(&resizeTimer,SIGNAL(timeout()),this,SLOT(timerEvent()));
   mapPos = QPoint(400,300);
   this->setMouseTracking(true);
   lastMousePos = middle;
   zoomSpeed = BASEZOOMSPEED;
   //
   // FOR TESTING, PLEASE REMOVE
   //
   icons.push_back(new FacilityIcon(QPoint(200,100),"Franklin Hospital","Eastern Counties"));
   icons.push_back(new FacilityIcon(QPoint(-MAPMIDDLEX,-MAPMIDDLEY),"General Hospital","Renfrew County"));
   for(int i=0;i<17;i++)
    icons.push_back(new FacilityIcon(QPoint(rand()%500 - 250,rand()%100 - 50),"General Hospital","Renfrew County"));
   //
   //
   //
   mapX = new MapMarker(QPoint(-10,-10),parent);
    setGeometry(0,0,400,300);
}
/**
 * Destructor for MapArea. Deletes any mapvectors that the area may have
 *
 */
MapArea::~MapArea()
{
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        delete *iter;
        iter++;
    }
    vecs.clear();
    QVector<FacilityIcon*>::iterator fiter = icons.begin();
    while(fiter != icons.end())
    {
        delete *fiter;
        fiter++;
    }
    icons.clear();
    delete mapX;
}

QVector<MapVectors*>& MapArea::getVecs()
{
    return vecs;
}
/**
 * Draws all mapvectors the map area contains along with the facility icons.
 *
 */
void MapArea::paintEvent(QPaintEvent *)
{
    setGeometry(0,0,middle.x()*2,middle.y()*2);
    QPainter painter(this);
    //Draw Background
    //painter.setViewport(0,0,middle.x()*2,middle.y()*2);

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(0,0,middle.x()*2,middle.y()*2));
    painter.setBrush(Qt::transparent);
    painter.setPen(Qt::black);
    painter.drawRect(QRect(10,10, middle.x()*2-20, middle.y()*2-20));
    for(int i=0;i<this->vecs.count();i++)
    {
        painter.setPen(vecs.at(i)->getCol().darker());
        painter.setBrush(vecs.at(i)->getCol().lighter(130));
        painter.drawPolygon(vecs.at(i)->getPoly());
        //painter.drawEllipse(vecs.at(i)->getRealPosition() + mapPos,10,10);
    }
    for(int i=0;i<icons.count();i++)
    {
        icons.at(i)->draw(painter);
    }
    mapX->draw(painter);
    QPoint lastMousePos = this->lastMousePos;
    lastMousePos += QPoint(MAPMIDDLEX,MAPMIDDLEY);
    lastMousePos -= mapPos;
    painter.drawText(10,middle.y()*2 - 40,"X: " + QString::number(lastMousePos.x()) + " Y: " + QString::number(lastMousePos.y()));
    //painter.drawEllipse(mapPos,15,15);
    //painter.drawEllipse(middle,10,10);
}
/**
 * Adds a mapvector to the map. A mapvector is a specific series of points that resembles a reigon on the map
 *
 * @param points the points of the polygon of the reigon
 * @param col the color that the reigon will show
 */
void MapArea::addVecs(QString reg,QVector<QPoint>* points, QColor col)
{
    MapVectors* temp = new MapVectors(reg,col);
    temp->setVectors(points);
    temp->setMiddle(middle);
    vecs.push_back(temp);
}
/**
 * the timer which will move the map into the center of the screen, and resize all areas and icons
 *
 */
void MapArea::timerEvent()
{
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        (*iter)->update(lastMousePos);
        iter++;
    }
    QVector<FacilityIcon*>::iterator fiter = icons.begin();
    while(fiter != icons.end())
    {
        (*fiter)->update(lastMousePos);
        fiter++;
    }
    mapX->update(lastMousePos);
    moveMap();
    repaint();
}
/**
 * resizes all areas and icons about a point p
 *
 * @param p the point about which the icons and areas will resize
 */
void MapArea::resize(QPoint p)
{
    QVector<MapVectors*>::iterator viter = vecs.begin();
    QVector<FacilityIcon*>::iterator fiter = icons.begin();
   // zoomSpeed = middle.manhattanLength() *BASEZOOMSPEED / QPoint(500,400).manhattanLength();
    float scale = 1;

        if(zoomed)
        {
            if(MapVectors::checkZoomOut(vecs, p))
            {
               // scale = 0.66;
                scale = 1/zoomSpeed;
                zoomed = false;
                lastMousePos = middle;
            }
        }
        else
        {
            //scale = 1.5;
            scale = zoomSpeed;
            zoomed = true;
        }

        if((!MapVectors::checkZoomOut(vecs, p)&& zoomed)||
           (MapVectors::checkZoomOut(vecs, p)&& !zoomed)||
           (MapVectors::checkZoomOut(vecs, p)&& zoomed))
        {
            while(viter != vecs.end())
            {
                 (*viter)->resizePoints(p,scale);
                 viter++;
            }
            while(fiter != icons.end())
            {
                 (*fiter)->resizePoints(p,scale);
                 fiter++;
            }

        }
        mapX->resizePoints(p,scale);


    viter = vecs.begin();
    fiter = icons.begin();
    while(viter != vecs.end())
    {
        (*viter)->checkSetSelected(p);
        viter++;
    }
    while(fiter != icons.end())
    {
         if((*fiter)->checkSetSelected(p))
         {
             break;
         }
         fiter++;
    }
    mapX->setPosition(p);


    repaint();
}
/**
 * Event triggered when mouse is down, position saved, and the resize method is called to zoom in
 *
 * @param event used to find x and y coordinates of mouse when pressed
 */
void MapArea::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = QPoint(event->x(),event->y());
    resize(lastMousePos);
    updateLabels();
}

void MapArea::mouseReleaseEvent(QMouseEvent *)
{

}

void MapArea::mouseClickEvent(QMouseEvent *)
{

}

void MapArea::setMiddle(QPoint& middle)
{
    MapArea::middle = middle;

    MapVectors::setMiddle(middle);
    FacilityIcon::setMiddle(middle);
    MapMarker::setMiddle(middle);

}
/**
 * Finds the ideal position for the map to be in and moves it towards that location
 *
 *
 */
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
            lastMousePos.rx() += cos(angle)*MOVESPEED;
            lastMousePos.ry() += sin(angle)*MOVESPEED;
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
            lastMousePos.rx() -= cos(angle)*MOVESPEED;
            lastMousePos.ry() -= sin(angle)*MOVESPEED;
        }
    }
    QVector<MapVectors*>::iterator iter = vecs.begin();
    while(iter != vecs.end())
    {
        QPolygonF& p = (*iter)->getPoly();
        p.translate(mapPos);
        iter++;
    }
    QVector<FacilityIcon*>::iterator fiter = icons.begin();
    while(fiter != icons.end())
    {
        (*fiter)->move(mapPos);
        fiter++;
    }
    mapX->move(mapPos);
}
/**
 * Used to determine if the mouse is hovering over an area
 *
 * @param event used to find x and y coordinates of mouse when pressed
 */
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
/**
 * Loads in all the labels on the right hand side so that their values can be changed.
 *
 * @param labels the labels in which maparea takes control
 */
void MapArea::loadLabels(QVector<QLabel*> labels)
{
    this->labels = labels;

    for(int i=0;i<labels.size();i++)
    {
        labels.at(i)->setFont(QFont("Arial",10,3));
        labels.at(i)->setText("");
    }
}
/**
 * Resets the labels based on the current facility selected
 *
 *
 */
void MapArea::updateLabels()
{
    for(int i=0;i<labels.size();i++)
    {
        labels.at(i)->setText("");
    }
    for(int i=0;i<icons.count();i++)
    {
        if(icons.at(i)->isSelected())
        {
            labels.at(0)->setText(icons.at(i)->getName());
            //labels.at(1)->setText(icons.at(i)->getArea());
            labels.at(2)->setText("LTC: " + QString::number(icons.at(i)->getLTC())+"%");
            labels.at(3)->setText("CCC: " + QString::number(icons.at(i)->getCCC())+"%");
            labels.at(4)->setText("AC: " + QString::number(icons.at(i)->getAC())+"%");
            labels.at(5)->setText("X: "+QString::number(icons.at(i)->getPosition().x()) + " Y: "+QString::number(icons.at(i)->getPosition().y()));
        }
    }
    for(int i=0;i<vecs.count();i++)
    {
        if(vecs[i]->isSelected())
        {
            labels.at(1)->setText(vecs[i]->getRegion());
        }
    }
}

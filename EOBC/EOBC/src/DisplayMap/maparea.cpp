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
    scale = 1;
    connect(&resizeTimer,SIGNAL(timeout()),this,SLOT(timerEvent()));
    mapPos = QPoint(400,300);
    this->setMouseTracking(true);
    lastMousePos = middle;
    zoomSpeed = BASEZOOMSPEED;
    resizeTimer.stop();
    mouseDown = false;
    labelBoxColors = new QColor[4];
    for(int i=0;i<4;i++)
    {
        labelBoxColors[i] = QColor(Qt::transparent);
    }
    setGeometry(0,0,MAPMIDDLEX*2,MAPMIDDLEY*2);
    //this->setFixedSize(1700,1000);
   //
   // FOR TESTING, PLEASE REMOVE
   //
   //icons.push_back(new FacilityIcon(QPoint(-MAPMIDDLEX,-MAPMIDDLEY),"General Hospital","Renfrew County"));
   //loadIcon();
   //
   //
   //
   mapX = new MapMarker(QPoint(-10,-10),parent);
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
    //this->paintEvent(pe);
    QPainter g(this);
    if(geometry().height() < 400)
        setGeometry(0,0,middle.x()*2,middle.y()*2);
    //Draw Background
    //g.setViewport(0,0,middle.x()*2,middle.y()*2);

    g.setPen(Qt::white);
    g.setBrush(Qt::white);
    g.drawRect(QRect(0,0,middle.x()*2,middle.y()*2));
    g.setBrush(Qt::transparent);
    g.setPen(Qt::black);
    for(int i=0;i<this->vecs.count();i++)
    {
        g.setPen(vecs.at(i)->getCol().darker());
        g.setBrush(vecs.at(i)->getCol().lighter(130));
        g.drawPolygon(vecs.at(i)->getPoly());
        //g.drawEllipse(vecs.at(i)->getRealPosition() + mapPos,10,10);
    }
    for(int i=0;i<icons.count();i++)
    {
        icons.at(i)->draw(g);
    }
    mapX->draw(g);
    if(mouseDown)
    {
        //g.setBackgroundMode(Qt::TransparentMode);
        g.setBrush(QColor(100,100,255,100));
        g.drawRect(QRect(lastMousePos,curMousePos));
    }
    QPoint lastMousePos = this->lastMousePos;
    lastMousePos += QPoint(MAPMIDDLEX,MAPMIDDLEY);
    lastMousePos -= mapPos;
    g.drawText(15,middle.y()*2 - 40,"X: " + QString::number(lastMousePos.x()) + " Y: " + QString::number(lastMousePos.y()));

    g.setPen(Qt::black);
    g.setBrush(Qt::transparent);
    g.drawRect(QRect(0,0, middle.x()*2-1, middle.y()*2-4));
    for (int i=0;i<4;i++)
    {
        g.setPen(labelBoxColors[i].darker());
        g.setBrush(labelBoxColors[i]);
        g.drawRect(QRect(middle.x()*2-20,middle.y()/1.12+i*30 ,20,20));
    }
   // QPainter painter(this);
    //painter.drawPixmap(0,0,offimage);
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
    setGeometry(0,0,middle.x()*2,middle.y()*2);
    repaint();
}
/**
 * resizes all areas and icons about a point p
 *
 * @param p the point about which the icons and areas will resize
 */
void MapArea::resize(QPoint p, SelectType st)
{


    QVector<MapVectors*>::iterator viter = vecs.begin();
    QVector<FacilityIcon*>::iterator fiter = icons.begin();
   // zoomSpeed = middle.manhattanLength() *BASEZOOMSPEED / QPoint(500,400).manhattanLength();
    scale = 1;
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
        if(st == MapArea::POINTSELECT)
        {
             if((*fiter)->checkSetSelected(p))
             {
                 break;
             }
        }
        else
        {
           (*fiter)->checkSetSelectedBox(lastMousePos,curMousePos);
        }
        fiter++;
    }
    mapX->setPosition(p);
}
/**
 * Event triggered when mouse is down, position saved, and the resize method is called to zoom in
 *
 * @param event used to find x and y coordinates of mouse when pressed
 */
void MapArea::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = QPoint(event->x(),event->y());
    mouseDown = true;
}

void MapArea::mouseReleaseEvent(QMouseEvent *)
{

    QPoint xpos = (curMousePos + lastMousePos)/2;
    QPoint middle;
    middle.setX(this->middle.x());
    middle.setY(this->middle.y());
    if((curMousePos - lastMousePos).manhattanLength()>4)
    {

        resize(xpos,BOXSELECT);
        updateLabels(BOXSELECT);
    }
    if((curMousePos - lastMousePos).manhattanLength()<4)
    {
        resize(xpos,POINTSELECT);
        updateLabels(POINTSELECT);
    }
    setGeometry(0,0,MAPMIDDLEX*2,MAPMIDDLEY*2);
    mouseDown = false;
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
    setGeometry(0,0,middle.x()*2,middle.y()*2);
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
 /** loadIcon is called whenever a facility is sent from getData
   * the facility parameter is parsed, and a new facilityIcon is added to the map.
   *
   * @param f The pointer to the facility given by GetData
   */
void MapArea::loadIcon(Facility* f)
{
    if(f->getAreaThisIsIn())
    {
       /* for(int i=0;i<17;i++)
        {
           icons.push_back(new FacilityIcon(QPoint(rand()%700 - 250,rand()%150 - 50),"General Hospital","Renfrew County"));
           FacilityIcon::makeCollisionIcons(icons.at(icons.count()-1),icons);
        }*/
        int* percents = new int[4];
        foreach(FacilityIcon* ic , icons)
        {
            if(ic->getName() == f->getFacilityName())
            {
                int numLTCbeds = f->getNumBeds(Convenience::intToCareType(EOBC::LTC));
                if(numLTCbeds==0)
                {
                    percents[0] = f->getNumBedsOccupied(Convenience::intToCareType(EOBC::AC)); //ccc occ
                    percents[1] = f->getNumBedsOccupied(Convenience::intToCareType(EOBC::CCC));//ac occ
                    percents[2] = f->getNumBedsAvailable(Convenience::intToCareType(EOBC::AC));
                    percents[3] = f->getNumBedsAvailable(Convenience::intToCareType(EOBC::CCC));
                    ic->setPercents(percents);
                }
                else
                {
                    percents[0] = f->getNumBedsOccupied(Convenience::intToCareType(EOBC::LTC));
                    percents[1] = f->getNumBedsAvailable(Convenience::intToCareType(EOBC::LTC));
                    percents[2] = 0;
                    percents[3] = 0;
                    ic->setPercents(percents);
                }
                return;
            }
        }


        int iconType = Convenience::HOSPITAL;
        if(f->getNumBeds(Convenience::intToCareType(EOBC::LTC))==0)
        {
            percents[0] = f->getNumBedsOccupied(Convenience::intToCareType(EOBC::AC)); //ccc occ
            percents[1] = f->getNumBedsOccupied(Convenience::intToCareType(EOBC::CCC));//ac occ
            percents[2] = f->getNumBedsAvailable(Convenience::intToCareType(EOBC::AC));
            percents[3] = f->getNumBedsAvailable(Convenience::intToCareType(EOBC::CCC));
        }
        else
        {
            iconType = Convenience::LONGTERMCARE;
            percents[0] = f->getNumBedsOccupied(Convenience::intToCareType(EOBC::LTC));
            percents[1] = f->getNumBedsAvailable(Convenience::intToCareType(EOBC::LTC));
            percents[2] = 0;
            percents[3] = 0;
        }
        icons.push_back(new FacilityIcon(f->getLocation()-QPoint(MAPMIDDLEX,MAPMIDDLEY),f->getFacilityName(),"Out Of Area",iconType));
        icons.at(icons.count()-1)->setPercents(percents);
        icons.at(icons.count()-1)->setScale(scale);
        icons.at(icons.count()-1)->resizePoints(middle,scale);

        /*
        for(int i=0;i<vecs.count();i++) // IF THE FACILITY DOESNT KNOW WHAT AREA IT IS IN
        {
            QPolygonF p = vecs.at(i)->getPoly();
            p.translate(QPoint(MAPMIDDLEX,MAPMIDDLEY));
            QPoint Ipos = icons.at(icons.count()-1)->getPosition();
            if(p.containsPoint(Ipos,Qt::OddEvenFill))
            {
                icons.at(icons.count()-1)->setArea(vecs.at(i)->getRegion());
            }
        }*/
        icons.at(icons.count()-1)->setArea(Convenience::areaIDtoQString(f->getAreaThisIsIn()->getAreaId()));



        FacilityIcon::makeCollisionIcons(icons.at(icons.count()-1),icons);
    }
}
void MapArea::loadWaitingList(ID id,int count)
{
    for(int i=0;i<vecs.count();i++)
    {
        if(vecs.at(i)->getRegion()==Convenience::areaIDtoQString(id))
           vecs.at(i)->setWaitingListNum(count);
    }
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
    curMousePos = QPoint(event->x(),event->y());
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
/** The method updateLabels in MapArea handles the labels created in Map
 * It resets the labels based on the current facility or area selected
 *
 * @param st the current select type, can be box or point select type
 */
void MapArea::updateLabels(SelectType st)
{
    Q_UNUSED(st);

    for(int i=0;i<labels.size();i++)
    {
        labels.at(i)->setText("");
    }
    bool iconSelected = false;
    for(int j=0;j<4;j++)
        labelBoxColors[j] = Qt::transparent;
    for(int i=0;i<icons.count();i++)
    {
        if(icons.at(i)->isSelected())
        {
            labels.at(0)->setText(icons.at(i)->getName());
            labels.at(1)->setText(icons.at(i)->getArea());
            if(icons.at(i)->getType()== Convenience::HOSPITAL)
            {
                labels.at(2)->setText("AC: " + QString::number(icons.at(i)->getAC())+"/"+QString::number(icons.at(i)->getMaximum()));
                labels.at(3)->setText("CCC: " + QString::number(icons.at(i)->getCCC())+"/"+QString::number(icons.at(i)->getMaximum()));
                labels.at(4)->setText("Open AC Beds: " + QString::number(icons.at(i)->getACOpen())+"/"+QString::number(icons.at(i)->getMaximum()));
                labels.at(5)->setText("Open CCC Beds: " + QString::number(icons.at(i)->getCCCOpen())+"/"+QString::number(icons.at(i)->getMaximum()));

            }
            if(icons.at(i)->getType()== Convenience::LONGTERMCARE)
            {
                labels.at(2)->setText("LTC: " + QString::number(icons.at(i)->getLTC())+"/"+QString::number(icons.at(i)->getMaximum()));
                labels.at(3)->setText("Open Beds: " + QString::number(icons.at(i)->getLTCOpen())+"/"+QString::number(icons.at(i)->getMaximum()));
                labels.at(4)->setText("");
                labels.at(5)->setText("");
            }
            for(int j=0;j<4;j++)
                labelBoxColors[j] = icons.at(i)->getColors()[j];
            labels.at(6)->setText("X: "+QString::number(icons.at(i)->getPosition().x()) + " Y: "+QString::number(icons.at(i)->getPosition().y()));
            iconSelected = true;
        }
    }
    if(!iconSelected)
    {
        for(int i=0;i<vecs.count();i++)
        {
            if(vecs[i]->isSelected())
            {
                labels.at(1)->setText(vecs[i]->getRegion());
                labels.at(7)->setText("Size: "+QString::number(vecs[i]->getWaitingListNum()));
            }
        }
    }

}
void MapArea::resizeEvent(QResizeEvent *)
{
    setGeometry(0,0,middle.x()*2,middle.y()*2);
}

void MapArea::startTimer()
{
    resizeTimer.start(10);
}

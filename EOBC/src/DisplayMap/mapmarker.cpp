#include "mapmarker.h"
 /** The constructor for MapMarker, takes in a position and then calls
   * MapItem's constructor
   * @param pos The position of where the cross will start
   * @param parent Just passed to the MapItem constructor
   */
MapMarker::MapMarker(QPoint pos,QObject* parent) : MapItem(parent)
{
    position = pos;
}
 /** Draw uses the markers position to draw two lines
   * that represents a cross. Also calls the MapItem's draw method
   * @param g The painter from the MapArea widget
   */
void MapMarker::draw(QPainter& g)
{
    MapItem::draw(g);
    g.setPen(Qt::black);
    g.setBrush(Qt::blue);

    g.drawLine(QPoint(-5,-5)+realPosition + mapPos,QPoint(5,5)+realPosition + mapPos);
    g.drawLine(QPoint(5,-5)+realPosition + mapPos,QPoint(-5,5)+realPosition + mapPos);
    //g.drawEllipse(realPosition + mapPos,ICONSIZE*scale,ICONSIZE*scale);
    //QRect rect(realPosition+mapPos-QPoint(ICONRADIUS,ICONRADIUS)*scale,realPosition + mapPos +QPoint(ICONRADIUS,ICONRADIUS)*scale);

}
 /** Update just takes the mouse position, and passes it to the MapItem's
   * update method.
   * @see MapItem::update(QPoint)
   * @param mouse The position of the mouse, or the last known location of the mouse
   */
void MapMarker::update(QPoint mouse)
{
    //position -= mapPos;
    MapItem::update(mouse);
    //position += mapPos;
}
 /** move just updates the mapPos variable of MapMarker
   * @param mPos The middle position of the map on the screen
   */
void MapMarker::move(QPoint mPos)
{
    mapPos = mPos;
}
/** ResizePoints just takes the mouse position, and the requested scale, and passes it to
  * the MapItem's resizePoints method.
  * @see MapItem::resizePoints(QPoint, float)
  * @param mouse The position of the mouse, or the last known location of the mouse
  * @param scale The requested scale of the map
  */
void MapMarker::resizePoints(QPoint mouse, float scale)
{
    MapItem::resizePoints(mouse,scale);
}
void MapMarker::setPosition(QPoint mouse)
{
    this->position = mouse;
    position -= mapPos;
    position /= scale;
    MapItem::update(mouse);
    //MapItem::resizePoints(mouse,scale);
}


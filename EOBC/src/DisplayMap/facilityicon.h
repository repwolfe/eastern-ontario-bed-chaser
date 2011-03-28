#ifndef FACILITYICON_H
#define FACILITYICON_H

#include <QObject>
#include <QtGui/QPainter>
#include "mapitem.h"
#include <qmath.h>

/** The facilityicon class is the graphical representation of the facilities on the map.
  * It has the functionality to move itself around the map based on the scale and center of the map.
  * It also shows graphically the state of the facility based on the number of beds available.
  *
  * This class fufills the requirement of showing graphically to the users the occupancy rate of the facilities.
  */

class FacilityIcon : public MapItem
{
public:
    explicit FacilityIcon(QPoint pos,QString name, QString area, QObject *parent = 0);
    void draw(QPainter& g);
    void update(QPoint mouse);
    void move(QPoint mPos);
    void resizePoints(QPoint mouse, float scale);
    bool checkSetSelected(QPoint);
    QString getName();
    QString getArea();
    QPoint getPosition();
    float getLTC();
    float getCCC();
    float getAC();
signals:

public slots:

private:
    QPoint mapPos;
    float *piePercent;
    QColor *pieColor;
    QString name;
    QString area;
    static int iconNum;


};

#endif // FACILITYICON_H

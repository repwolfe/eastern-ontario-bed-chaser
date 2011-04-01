#ifndef FACILITYICON_H
#define FACILITYICON_H

#include <QObject>
#include <QtGui/QPainter>
#include "mapitem.h"
#include <qmath.h>
#include "convenience.h"
/**
  * @brief The facilityicon class is the graphical representation of the facilities on the map.
  *
  * It has the functionality to move itself around the map based on the scale and center of the map.
  * It also shows graphically the state of the facility based on the number of beds available.
  *
  * This class fufills the requirement of showing graphically to the users the occupancy rate of the facilities.
  */

class FacilityIcon : public MapItem
{

public:
    explicit FacilityIcon(QPoint pos,QString name, QString area,int type, QObject *parent = 0);
    void draw(QPainter& g);
    void update(QPoint mouse);
    void move(QPoint mPos);
    void resizePoints(QPoint mouse, float scale);
    static void makeCollisionIcons(FacilityIcon* f, QVector<FacilityIcon*> icons);
    bool checkSetSelected(QPoint);
    bool checkSetSelectedBox(QPoint,QPoint);
    QString getName();
    QString getArea();
    QPoint getPosition();
    float getLTC();
    float getCCC();
    float getAC();
    float getLTCOpen();
    float getCCCOpen();
    float getACOpen();
    int getType();
    void setArea(QString area);
    void setCollided(bool col);
    void setPercents(int* per);

signals:

public slots:

private:
    QPoint mapPos;
    float *piePercent;
    QColor *pieColor;
    QString name;
    QString area;
    int type;
    static int iconNum;
    bool collidedIcon;


};

#endif // FACILITYICON_H

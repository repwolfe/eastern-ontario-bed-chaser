#ifndef FACILITYICON_H
#define FACILITYICON_H

#include <QObject>
#include <QtGui/QPainter>
#include "mapitem.h"
#include <qmath.h>
class FacilityIcon : public MapItem
{
public:
    explicit FacilityIcon(QPoint pos,QString name, QString area, QObject *parent = 0);
    void draw(QPainter& g);
    void update(QPoint mouse);
    void move(QPoint mPos);
    void resizePoints(QPoint mouse, float scale);
    QString getName();
    QString getArea();
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


};

#endif // FACILITYICON_H

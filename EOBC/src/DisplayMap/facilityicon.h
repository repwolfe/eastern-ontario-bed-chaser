#ifndef FACILITYICON_H
#define FACILITYICON_H

#include <QObject>
#include <QtGui/QPainter>
#include "mapitem.h"
class FacilityIcon : public MapItem
{
public:
    explicit FacilityIcon(QPoint pos,QObject *parent = 0);
    void draw(QPainter& g);
    void update(QPoint mouse);
    void move(QPoint mPos);

signals:

public slots:

private:
    QPoint mapPos;


};

#endif // FACILITYICON_H

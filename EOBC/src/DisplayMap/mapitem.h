#ifndef MAPITEM_H
#define MAPITEM_H

#include <QObject>
#include <QPainter>
class MapItem : public QObject
{
    Q_OBJECT
public:
    explicit MapItem(QObject *parent = 0);
    ~MapItem();
    virtual void draw(QPainter& g);
    virtual void update(QPoint mouse);
    virtual void resizePoints(QPoint mouse, float scale);

    static void setMiddle(QPoint&);
    virtual QPoint getRealPosition();
    virtual bool isSelected();
    virtual QPoint getPosition();
    virtual float getScale();
    virtual void setHovered(bool);


signals:

public slots:

private:
    MapItem(const MapItem&);

protected:
    float scale;
    float idealScale;
    QPoint position;
    QPoint realPosition;
    QPoint idealPosition;
    bool selected;
    bool hovered;
    static QPoint middle;


};

#endif // MAPITEM_H

#ifndef MAPVECTORS_H
#define MAPVECTORS_H

#include <QWidget>
#include <QMouseEvent>
#include <QList>
#include <QPainter>
class MapVectors : public QWidget
{
    Q_OBJECT
public:
    MapVectors(QColor col, QWidget *parent = 0);
    QVector<QPoint>& getVectors();
    void setVectors(QVector<QPoint>* ve);
    void update();
    void resizePoints();

signals:

public slots:

protected:
   /* void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);*/
    void paintEvent(QPaintEvent *event);
private:
    QVector<QPoint>* mapPoints;
    QImage* image;
   // QImage mapPic;
    QColor col;
};

#endif // MAPVECTORS_H

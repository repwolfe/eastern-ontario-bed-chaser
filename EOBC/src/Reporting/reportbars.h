#ifndef REPORTBARS_H
#define REPORTBARS_H

#include <QObject>
#include <QtGui/qpainter.h>
class ReportBars : public QObject
{
    Q_OBJECT
public:
    explicit ReportBars(QObject *parent = 0);
    void draw(QPainter& g);
signals:

public slots:
private:
    QPoint position;
    QPoint size;

};

#endif // REPORTBARS_H

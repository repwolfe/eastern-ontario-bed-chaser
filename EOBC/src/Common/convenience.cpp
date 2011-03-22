#include "convenience.h"
#include <QDesktopWidget>
#include <QApplication>

/**
 * Static convenience function that returns a QRect with size width and height at center of screen.
 *
 * @param width of the desired QRect
 * @param height of the desired QRect
 */
QRect Convenience::getCenterForSize(int width, int height)
{
    QDesktopWidget *d = QApplication::desktop();
    QRect rect(d->width()/2 - width/2, d->height()/2 - height/2, width, height);
    return rect;
}

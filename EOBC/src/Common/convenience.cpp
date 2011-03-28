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
/**
 * Static convenience function that returns an EOBC::CareType for a given integer
 *
 * @param care the integer, type of care
 * @return the type of care based on that integer, or LTC
 */
EOBC::CareType Convenience::intToCareType(int care){
    switch(care){
    case 0: return EOBC::AC;
        break;
    case 1: return EOBC::CCC;
        break;
    case 2: return EOBC::LTC;
        break;
    default: return EOBC::LTC;
        break;
    }

}

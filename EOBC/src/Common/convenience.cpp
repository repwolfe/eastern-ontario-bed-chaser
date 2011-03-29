#include "convenience.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QRegExpValidator>
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
EOBC::CareType Convenience::intToCareType(int care)
{
    switch(care){
	case 0: return EOBC::AC;
	case 1: return EOBC::CCC;
	case 2: return EOBC::LTC;
	default: return EOBC::LTC;
    }
}

/**
 * Static convenience function that returns an EOBC::CareType for a given QString
 *
 * @param care the QString, type of care
 * @return the type of care based on that integer, or LTC
 */
EOBC::CareType Convenience::qstringToCareType(QString care)
{
    if (care.trimmed() == "AC")
    {
	return EOBC::AC;
    }
    else if (care.trimmed() == "CCC")
    {
	return EOBC::CCC;
    }
    else if (care.trimmed() == "LTC")
    {
	return EOBC::LTC;
    }
    else
    {
	return EOBC::LTC;
    }
}

/**
 * Static convenience function that checks if a given health card number
 * is properly formated (####-###-###)
 *
 * @param hcn the health card number
 * @return True if formatted right, False otherwise
 */
bool Convenience::correctHealthCardNumber(QString hcn)
{
    QRegExp rx("[0-9]{4,4}-[0-9]{3,3}-[0-9]{3,3}");
    int pos = 0;
    QRegExpValidator v(rx, 0);
    return v.validate(hcn, pos);
}

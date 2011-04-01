#ifndef CONVENIENCE_H
#define CONVENIENCE_H

#include <QRect>
#include "modelcommon.h"

/**
 * @brief Class of static convenience functions
 *
 * This Class will only have static convenience functions
 * to help the developers avoid code repetition for
 * simple, generic tasks.
 *
 * @todo Traceability?
 */
class Convenience
{
public:
    enum {HOSPITAL = 0,LONGTERMCARE=1};
    static QRect getCenterForSize(int width, int height);
    static EOBC::CareType intToCareType(int care);
    static EOBC::CareType qstringToCareType(QString care);
    static bool correctHealthCardNumber(QString hcn);
    static QString areaIDtoQString(ID id);

private:
    Convenience();
};

#endif // CONVENIENCE_H

#ifndef CONVENIENCE_H
#define CONVENIENCE_H

#include <QRect>
#include "modelcommon.h"
#include <QDate>
#include <QString>

/**
 * @brief Class of static convenience functions
 *
 * This Class will only have static convenience functions
 * to help the developers avoid code repetition for
 * simple, generic tasks.
 *
 * This class implements common functions and provides services to all classes that require e.g. casting operators
 */
class Convenience
{
public:
    enum {
        HOSPITAL        = 0,
        LONGTERMCARE    = 1
    };
    enum UserType {
        FACILITYSTAFF        = 0,
        LHINSTAFF            = 1,
        ADMINISTRATOR        = 2
    };

    static const int NUM_AREAS;
    static QRect getCenterForSize(int width, int height);

    static EOBC::CareType intToCareType(int care);
    static EOBC::CareType qStringToCareType(QString care);
    static QString careTypeToQString(EOBC::CareType care);

    static bool correctHealthCardNumber(QString hcn);
    static QString areaIDtoQString(ID id);
    static QString toXML(QDate date);
    static QDate fromXML(QString date);
private:
    Convenience();
};

#endif // CONVENIENCE_H

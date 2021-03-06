#ifndef MODELCOMMON_H
#define MODELCOMMON_H

/// Key for Areas, Facilities
typedef int ID;

namespace EOBC
{
    /**
     * An enumerated type for different levels of bed care
     * Acute Care
     * Continuing Complex Care
     * Long Term Care
     */
    enum CareType
    {
	AC,
	CCC,
	LTC
    };
}

#endif // MODELCOMMON_H

#ifndef MODELCOMMON_H
#define MODELCOMMON_H

/**
 * An enumerated type for different levels of bed care
 * Acute Care
 * Continuing Complex Care
 * Long Term Care
 */
namespace EOBC
{
    enum CareType
    {
	AC,
	CCC,
	LTC
    };
}

#endif // MODELCOMMON_H

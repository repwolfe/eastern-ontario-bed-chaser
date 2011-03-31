#ifndef GETDATAREPORTINGINTERFACE_H
#define GETDATAREPORTINGINTERFACE_H

#include <QObject>
#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and Reporting subsystems
 *
 * @todo Description
 *
 * @todo traceability
 */
class GetDataReportingInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataReportingInterface(GetDataControl& getData);

signals:

public slots:

private:
    GetDataControl& _getData;

};

#endif // GETDATAREPORTINGINTERFACE_H

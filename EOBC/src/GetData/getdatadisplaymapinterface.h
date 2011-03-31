#ifndef GETDATADISPLAYMAPINTERFACE_H
#define GETDATADISPLAYMAPINTERFACE_H

#include <QObject>
#include "getdatacontrol.h"

/**
 * @brief Interface between the GetData and DisplayMap subsystems
 *
 * @todo Description
 *
 * @todo traceability
 */
class GetDataDisplayMapInterface : public QObject
{
    Q_OBJECT
public:
    explicit GetDataDisplayMapInterface(GetDataControl& getData);

signals:

public slots:

private:
    GetDataControl& _getData;

};

#endif // GETDATADISPLAYMAPINTERFACE_H

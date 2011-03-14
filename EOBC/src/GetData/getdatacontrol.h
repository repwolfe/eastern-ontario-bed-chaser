#ifndef GETDATACONTROL_H
#define GETDATACONTROL_H

#include <QString>
class GetDataControl
{
public:
    GetDataControl();

    /// @todo decide if these three interface functions should each be in their own class
    /// to prevent classes from having abilities they shouldn't
    QString sendRequestForData(QString& args);
    QString requestData(QString& args);
    bool checkLogOn(QString& usr, QString& pass);
};

#endif // GETDATACONTROL_H

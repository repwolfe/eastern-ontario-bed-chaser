#ifndef GETDATACONTROL_H
#define GETDATACONTROL_H

#include <QString>

/// @todo remove these
class StorageRead;
class SendRequestForData;
class SendDataResponse;

class GetDataControl
{
public:
    GetDataControl();

    /// @todo decide if these interface functions should each be in their own class
    /// to prevent classes from having abilities they shouldn't
    QString sendRequestForData(QString& args);
    QString requestData(QString& args);

private:
    StorageRead* _storage;
    SendRequestForData* _sendRequest;
    SendDataResponse* _sendResponse;
};

#endif // GETDATACONTROL_H

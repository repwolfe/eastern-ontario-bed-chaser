#ifndef CHANGEDATACONTROL_H
#define CHANGEDATACONTROL_H

#include <QString>

/// @todo remove these and include the classes when they're written
class StorageWrite;
class SendChangeDataRequest;

class ChangeDataControl
{
public:
    ChangeDataControl();

    bool changeData(QString& args, QString& data);

private:
    void _changeLocal(QString& args, QString& data);
    void _changeRemote(QString& args, QString& data);

    StorageWrite* _storage;
    SendChangeDataRequest* _sendData;
};

#endif // CHANGEDATACONTROL_H

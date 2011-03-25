#ifndef CHANGEDATACONTROL_H
#define CHANGEDATACONTROL_H

#include <QString>
#include <QObject>

#include "movepatientcontrol.h"

/// @todo remove these and include the classes when they're written
class StorageWrite;
class SendChangeDataRequest;

class ChangeDataControl : public QObject
{
    Q_OBJECT
public:
    ChangeDataControl();
    ~ChangeDataControl();

    void run();

    bool changeData(QString& args, QString& data);

public slots:
    void displayMovePatientsToBedForm();
    void displayMovePatientsToFacilityForm();

private:
    void _changeLocal(QString& args, QString& data);
    void _changeRemote(QString& args, QString& data);

    StorageWrite* _storage;
    SendChangeDataRequest* _sendData;

    // Child Control objects
    MovePatientControl* _movePatientControl;
};

#endif // CHANGEDATACONTROL_H

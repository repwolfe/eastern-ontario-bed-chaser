#ifndef CHANGEDATACONTROL_H
#define CHANGEDATACONTROL_H

#include <QString>
#include <QObject>

#include "movepatientcontrol.h"
#include "addpatientcontrol.h"
#include "addfacilitycontrol.h"

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
    void displayAddFacilityForm();
    void displayAddPatientForm();

    void movePatientsToBedSubmitted();
    void movePatientsToFacilitySubmitted();
    void addFacilitySubmitted(QString, QString, QString);
    void addPatientSubmitted(QString, QString, QString, QString);

private:
    void _changeLocal(QString& args, QString& data);
    void _changeRemote(QString& args, QString& data);

    StorageWrite* _storage;
    SendChangeDataRequest* _sendData;

    // Child Control objects
    MovePatientControl* _movePatientControl;
    AddFacilityControl* _addFacilityControl;
    AddPatientControl* _addPatientControl;
};

#endif // CHANGEDATACONTROL_H

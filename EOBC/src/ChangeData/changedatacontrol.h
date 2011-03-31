#ifndef CHANGEDATACONTROL_H
#define CHANGEDATACONTROL_H

#include <QString>
#include <QObject>

#include "getdatachangedatainterface.h"
#include "movepatientcontrol.h"
#include "addfacilitycontrol.h"
#include "createusercontrol.h"
#include "updatebedscontrol.h"
#include "updatewaitinglistcontrol.h"

/// @todo remove these and include the classes when they're written
class StorageWrite;
class SendChangeDataRequest;

/**
 * @brief Controller that controls other Controller objects.
 *
 * Specifically ones involved with forms which Change Data.
 * Listens for submissions and takes their information and gives
 * it to the database. Also informs other systems to update their
 * information with what was changed.
 *
 * This class is part of the ChangeData subsystem described in D2.
 */
class ChangeDataControl : public QObject
{
    Q_OBJECT
public:
    ChangeDataControl(GetDataChangeDataInterface& getData);
    ~ChangeDataControl();

    bool changeData(QString& args, QString& data);

signals:
    void receivedAllFacilities(const QMap<ID, QString>&);
    void receivedFacilitiesPatients(const QMap<ID, QLinkedList<Patient> >&);
    void receivedAreasWaitingList(const QMap<ID, QLinkedList<Patient> >&);
    void receivedFacilitiesCurrentBedNumbers(const QMap<ID, QLinkedList<int> >&);
    void receivedFacilitiesMinimumBedNumbers(const QMap<ID, QLinkedList<int> >&);

public slots:
    // Display GUI
    void displayMovePatientsToBedForm();
    void displayMovePatientsToFacilityForm();
    void displayAddFacilityForm();
    void displayCreateUserForm();
    void displayUpdateBedsForm();
    void displayUpdateWaitingList();

private slots:
    // Submissions
    void movePatientsToBedSubmitted();
    void movePatientsToFacilitySubmitted();
    void addFacilitySubmitted(QString, QString, QString);
    void addPatientSubmitted(QString, QString, QString, QString);
    void createUserSubmitted(QString, QString, QString, QString, QString);
    void updateBedsSubmitted(QString, int, int, int);
    void updateWaitingListSubmitted();

/*    // Get Data
    void requestAllFacilities();
    void requestFacilitiesPatients();
    void requestAreasWaitingList();
    void requestFacilitiesCurrentBedNumbers();
    void requestFacilitiesMinimumBedNumbers();
*/
    // Received Data
    void receivedAllFacilities();
    void receivedFacilitiesPatients();
    void receivedAreasWaitingList();
    void receivedFacilitiesCurrentBedNumbers();
    void receivedFacilitiesMinimumBedNumbers();
private:
    void _setupConnections();

    void _changeLocal(QString& args, QString& data);
    void _changeRemote(QString& args, QString& data);

    StorageWrite* _storage;
    SendChangeDataRequest* _sendData;

    GetDataChangeDataInterface& _getData;

    // Child Control objects
    MovePatientControl*		_movePatientControl;
    AddFacilityControl*		_addFacilityControl;
    CreateUserControl*		_createUserControl;
    UpdateBedsControl*		_updateBedsControl;
    UpdateWaitingListControl*	_updateWaitingListControl;
};

#endif // CHANGEDATACONTROL_H

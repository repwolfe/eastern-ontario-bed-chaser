#include "movepatientcontrol.h"

MovePatientControl::MovePatientControl()
{
    _toFacilityForm = new MovePatientForm("Move Patients to Facility", false, "To Facility");
    _toBedForm = new MovePatientForm("Move Patients to Bed", true, "To Bed");

    QStringList bedOptions;
    bedOptions.push_back("AC");
    bedOptions.push_back("CCC");
    /// @todo what to do about this
    bedOptions.push_back("LTC");
    _toBedForm->setMoveToItems(bedOptions);

    /// @todo remove this:
    QStringList patients;
    patients.push_back("Robbie");
    patients.push_back("JP");
    patients.push_back("Austin");

    QStringList facilities;
    facilities.push_back("Franklin General");
    facilities.push_back("Cedar Sinar");
    _toBedForm->setFacilityItems(facilities);
    _toBedForm->setPatientItems(patients);
}

MovePatientControl::~MovePatientControl()
{
    delete _toFacilityForm;
    delete _toBedForm;
}

void MovePatientControl::showToFacilityForm()
{
    _toFacilityForm->show();
}

void MovePatientControl::showToBedForm()
{
    _toBedForm->show();
}

#ifndef MOVEPATIENTCONTROL_H
#define MOVEPATIENTCONTROL_H

#include "movepatientform.h"

class MovePatientControl
{
public:
    MovePatientControl();
    ~MovePatientControl();

    void showToFacilityForm();
    void showToBedForm();

private:
    MovePatientForm* _toFacilityForm;
    MovePatientForm* _toBedForm;
};

#endif // MOVEPATIENTCONTROL_H

#include "addpatientcontrol.h"

AddPatientControl::AddPatientControl()
{
    form = new AddPatientForm();
    connect(form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

AddPatientControl::~AddPatientControl()
{
    delete form;
}

void AddPatientControl::showForm()
{
    form->clearContents();
    form->show();
}

void AddPatientControl::_submitClicked()
{
    emit submitClicked(form->getFirstName(), form->getLastName(),
                       form->getHealthCardNumber(), form->getRequiredCare());
    form->close();
}

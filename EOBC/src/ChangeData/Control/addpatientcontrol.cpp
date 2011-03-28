#include "addpatientcontrol.h"

AddPatientControl::AddPatientControl()
{
    _form = new AddPatientForm();
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

AddPatientControl::~AddPatientControl()
{
    delete _form;
}

void AddPatientControl::showForm()
{
    _form->clearContents();
    _form->show();
}

void AddPatientControl::_submitClicked()
{
    emit submitClicked(_form->getFirstName(), _form->getLastName(),
		       _form->getHealthCardNumber(), _form->getRequiredCare());
    _form->close();
}

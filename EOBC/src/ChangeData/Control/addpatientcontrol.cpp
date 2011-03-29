#include "addpatientcontrol.h"
#include "convenience.h"

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
    const QString& firstName	= _form->getFirstName().trimmed();
    const QString& lastName	= _form->getLastName().trimmed();
    const QString& hcn		= _form->getHealthCardNumber().trimmed();
    const QString& requiredCare = _form->getRequiredCare().trimmed();

    if (!firstName.isEmpty() && !lastName.isEmpty() &&
	Convenience::correctHealthCardNumber(hcn) && !requiredCare.isEmpty())
    {
	emit submitClicked(firstName, lastName, hcn, requiredCare);
	_form->close();
    }
    else
    {
	_form->displayError();
    }
}

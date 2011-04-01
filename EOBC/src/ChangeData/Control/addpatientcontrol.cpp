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

/**
 * Private slot for a submission
 * Removes whitespace and makes sure none of the fields are empty
 * Also checks if the health card number is properly formatted
 */
void AddPatientControl::_submitClicked()
{
    const QString& firstName	= _form->getFirstName().trimmed();
    const QString& lastName	= _form->getLastName().trimmed();
    const QString& hcn		= _form->getHealthCardNumber().trimmed();
    const QString& requiredCare = _form->getRequiredCare().trimmed();
    const QDate&   dateAdded    = _form->getDateAdded();

    if (!firstName.isEmpty() && !lastName.isEmpty() &&
	Convenience::correctHealthCardNumber(hcn) && !requiredCare.isEmpty())
    {
        emit submitClicked(firstName, lastName, hcn, requiredCare, dateAdded);
	_form->close();
    }
    else
    {
	_form->displayError();
    }
}

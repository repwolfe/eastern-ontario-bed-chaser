#include "addfacilitycontrol.h"

AddFacilityControl::AddFacilityControl()
{
    _form = new AddFacilityForm();
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

AddFacilityControl::~AddFacilityControl()
{
    delete _form;
}

void AddFacilityControl::showForm()
{
    _form->clearContents();
    _form->show();
}

void AddFacilityControl::_submitClicked()
{
    /// @todo Check for empty submissions
    const QString& name	    = _form->getFacilityName().trimmed();
    const QString& xAxis    = _form->getXAxis().trimmed();
    const QString& yAxis    = _form->getYAxis().trimmed();

    if (!name.isEmpty() && !xAxis.isEmpty() && !yAxis.isEmpty())
    {
	emit submitClicked(name, xAxis, yAxis);
	_form->close();
    }
    else
    {
	_form->displayError();
    }
}

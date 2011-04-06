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
    const QString& name	    = _form->getFacilityName().trimmed();
    const QString& xAxis    = _form->getXAxis().trimmed();
    const QString& yAxis    = _form->getYAxis().trimmed();
    const int area	    = _form->getCurrentAreaIndex();

    bool xOk = true;
    bool yOk = true;
    int xAsInt = xAxis.toInt(&xOk);
    int yAsInt = yAxis.toInt(&yOk);

    if (!name.isEmpty() && !xAxis.isEmpty() && !yAxis.isEmpty() &&
	xOk && yOk && xAsInt >= 0 && yAsInt >= 0)
    {
	emit submitClicked(name, area, xAxis, yAxis);
	_form->close();
    }
    else
    {
	_form->displayError();
    }
}

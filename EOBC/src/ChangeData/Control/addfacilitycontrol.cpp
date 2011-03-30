#include "addfacilitycontrol.h"

AddFacilityControl::AddFacilityControl()
{
    form = new AddFacilityForm();
    connect(form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

AddFacilityControl::~AddFacilityControl()
{
    delete form;
}

void AddFacilityControl::showForm()
{
    form->clearContents();
    form->show();
}

void AddFacilityControl::_submitClicked()
{
    /// @todo Check for empty submissions
    emit submitClicked(form->getFacilityName(), form->getXAxis(), form->getYAxis());
    form->close();
}

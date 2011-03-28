#include "updatebedscontrol.h"

UpdateBedsControl::UpdateBedsControl()
{
    form = new UpdateBedsForm();
    connect(form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

UpdateBedsControl::~UpdateBedsControl()
{
    delete form;
}

void UpdateBedsControl::showForm()
{
    /// @todo populate with real data! :)
    form->show();
}

void UpdateBedsControl::_submitClicked()
{
    emit submitClicked(form->getCurrentFacility(), form->getNumAC(),
		       form->getNumCCC(), form->getNumLTC());
    form->close();
}

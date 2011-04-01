#include "updatebedscontrol.h"

UpdateBedsControl::UpdateBedsControl()
{
    _form = new UpdateBedsForm();
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

UpdateBedsControl::~UpdateBedsControl()
{
    delete _form;
}

void UpdateBedsControl::showForm()
{
    /// @todo populate with real data! :)
    _form->show();
}

void UpdateBedsControl::setFacilitiesList(const QMap<ID, QString>& data)
{
    /// @todo implement
}

void UpdateBedsControl::setCurrentBedNumbers(const QMap<ID, QVector<int> >& data)
{
    /// @todo implement
}

void UpdateBedsControl::setMinimumBedNumbers(const QMap<ID, QVector<int> >& data)
{
    /// @todo implement
}

void UpdateBedsControl::_submitClicked()
{
    emit submitClicked(_form->getCurrentFacility(), _form->getNumAC(),
		       _form->getNumCCC(), _form->getNumLTC());
    _form->close();
}

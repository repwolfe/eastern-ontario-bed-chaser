#include "updatebedscontrol.h"

UpdateBedsControl::UpdateBedsControl()
{
    _form = new UpdateBedsForm();
    _waitingForFacilitiesList = false;
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

UpdateBedsControl::~UpdateBedsControl()
{
    delete _form;
}

void UpdateBedsControl::waitingForData()
{
    _waitingForFacilitiesList = true;
}

void UpdateBedsControl::showForm()
{
    _form->show();
}

void UpdateBedsControl::setFacilitiesList(const QMap<ID, QString>& data)
{
    QStringList facilities;

    if (_waitingForFacilitiesList)
    {
	_waitingForFacilitiesList = false;
	QMap<ID, QString>::const_iterator iter = data.begin();
	int index = 0;
	while (iter != data.end())
	{
	    facilities << iter.value();
	    _indexToFacilityId[index] = iter.key();
	    ++index;
	    ++iter;
	}
	_form->setFacilityItems(facilities);
    }
}

void UpdateBedsControl::setCurrentBedNumbers(const QMap<ID, QVector<int> >& data)
{
    _currentBedNumbers = data;
}

void UpdateBedsControl::setMinimumBedNumbers(const QMap<ID, QVector<int> >& data)
{
    _minimumBedNumbers = data;
}

void UpdateBedsControl::_facilitySelected(int index)
{
    QMap<int, ID>::const_iterator find = _indexToFacilityId.find(index);
    if (find != _indexToFacilityId.end())
    {
	QMap<ID, QVector<int> >::const_iterator cur = _currentBedNumbers.find(find.value());
	if (cur != _currentBedNumbers.end())
	{
	    const QVector<int>& beds = cur.value();
	    _form->setNumAC(beds[0]);
	    _form->setNumCCC(beds[1]);
	    _form->setNumLTC(beds[2]);
	}
	QMap<ID, QVector<int> >::const_iterator min = _minimumBedNumbers.find(find.value());
	if (min != _minimumBedNumbers.end())
	{
	    const QVector<int>& beds = cur.value();
	    _form->setMinimumAC(beds[0]);
	    _form->setMinimumCCC(beds[1]);
	    _form->setMinimumLTC(beds[2]);
	}
    }
}

void UpdateBedsControl::_submitClicked()
{
    emit submitClicked(_form->getCurrentFacilityIndex(), _form->getNumAC(),
		       _form->getNumCCC(), _form->getNumLTC());
    _form->close();
}

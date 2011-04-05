#include "updatebedscontrol.h"

UpdateBedsControl::UpdateBedsControl()
{
    _form = new UpdateBedsForm();
    _waitingForFacilitiesList = false;
    _waitingForCurrentBeds = false;
    _waitingForMinBeds = false;
    connect(_form, SIGNAL(facilitySelected(int)), SLOT(_facilitySelected(int)));
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

UpdateBedsControl::~UpdateBedsControl()
{
    delete _form;
}

/**
 * Used to indicate that this control is waiting for data
 */
void UpdateBedsControl::waitingForData()
{
    _waitingForFacilitiesList = true;
    _waitingForCurrentBeds = true;
    _waitingForMinBeds = true;
}

void UpdateBedsControl::showForm()
{
    _form->show();
}

/**
 * Upon receiving the map of facility id to its names, stores
 * the index of each facility and puts it in the drop down menu
 *
 * @param data map of facility id to name
 */
void UpdateBedsControl::setFacilitiesList(const QMap<ID, Facility*>& data)
{
    QStringList facilities;

    if (_waitingForFacilitiesList)
    {
	_waitingForFacilitiesList = false;
	QMap<ID, Facility*>::const_iterator iter = data.begin();
	int index = 0;
	while (iter != data.end())
	{
	    facilities << iter.value()->getFacilityName();
	    _indexToFacilityId[index] = iter.key();
	    ++index;
	    ++iter;
	}
	_form->setFacilityItems(facilities);
    }
}

/**
 * Sets the current bed numbers map to this, and if all the bed numbers
 * have been received, refreshes the values in the GUI
 *
 * @param map of facility id to a vector of its current bed numbers
 */
void UpdateBedsControl::setCurrentBedNumbers(const QMap<ID, QVector<int> >& data)
{
    _currentBedNumbers = data;
    _waitingForCurrentBeds = false;
    if (!_waitingForMinBeds)
    {
	_facilitySelected(0);
    }
}

/**
 * Sets the minimum bed numbers map to this, and if all the bed numbers
 * have been received, refreshes the values in the GUI
 *
 * @param map of facility id to a vector of its minimum bed numbers
 */
void UpdateBedsControl::setMinimumBedNumbers(const QMap<ID, QVector<int> >& data)
{
    _minimumBedNumbers = data;
    _waitingForMinBeds = false;
    if (!_waitingForCurrentBeds)
    {
	_facilitySelected(0);
    }
}

/**
 * When a facility is selected, get the current/minimum bed numbers
 * and adjust the dials accordingly
 *
 * @param index of the selected facility, ID found in the map
 */
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
	    const QVector<int>& beds = min.value();
	    _form->setMinimumAC(beds[0]);
	    _form->setMinimumCCC(beds[1]);
	    _form->setMinimumLTC(beds[2]);
	}
    }
}

void UpdateBedsControl::_submitClicked()
{
    int index = _form->getCurrentFacilityIndex();
    QMap<int, ID>::const_iterator find = _indexToFacilityId.find(index);
    if (find != _indexToFacilityId.end())
    {
	emit submitClicked(find.value(), _form->getNumAC(),
			   _form->getNumCCC(), _form->getNumLTC());
    }
    _form->close();
}

#include "sendchangedatainterface.h"

SendChangeDataInterface::SendChangeDataInterface(SendMessageControl& sendMessage)
    : _sendMessage(sendMessage)
{
}

/**
 * Sends an Add message
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area the patients will be added to
 * @param aFacility the Facility the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendChangeDataInterface::addPatients(bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p)
{
    _sendMessage.addPatients(remote, anArea, aFacility, p);
}

/**
 * Sends a Delete message
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area the patients will be added to
 * @param aFacility the Facility the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendChangeDataInterface::deletePatients(bool remote, Area* anArea, Facility* aFacility, QList<Patient*> p)
{
    _sendMessage.deletePatients(remote, anArea, aFacility, p);
}

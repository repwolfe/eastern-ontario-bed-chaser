#include "sendchangedatainterface.h"

SendChangeDataInterface::SendChangeDataInterface(SendMessageControl& sendMessage)
    : _sendMessage(sendMessage)
{
}

/**
 * Sends an Add message for adding to facility
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area with the Facility that the patients will be added to
 * @param aFacility the Facility the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendChangeDataInterface::addPatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p)
{
    _sendMessage.addPatients(remote, anArea, aFacility, p);
}

/**
 * Sends an Add message for adding to waiting list
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendChangeDataInterface::addPatients(bool remote, Area* anArea, QLinkedList<Patient*> p)
{
    _sendMessage.addPatients(remote, anArea, p);
}

/**
 * Sends a Delete message for removing patients from a facility
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area the patients will be added to
 * @param aFacility the Facility the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendChangeDataInterface::deletePatients(bool remote, Area* anArea, Facility* aFacility, QLinkedList<Patient*> p)
{
    _sendMessage.deletePatients(remote, anArea, aFacility, p);
}

/**
 * Sends a Delete message for removing patients from a waiting list
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param anArea the Area with the waiting list the patients will be added to
 * @param p the list of Patients that will be transformend into an XML tag
 */
void SendChangeDataInterface::deletePatients(bool remote, Area* anArea, QLinkedList<Patient*> p)
{
    _sendMessage.deletePatients(remote, anArea, p);
}


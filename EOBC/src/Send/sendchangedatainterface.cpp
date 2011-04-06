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

/**
 * Sends an addBed message
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param aFacility the Facility to add beds to
 * @param deltaACBeds the amount of beds to add
 * @param deltaCCCBeds the amount of beds to add
 * @param deltaLTCBeds the amount of beds to add
 */
void SendChangeDataInterface::addBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds)
{
    _sendMessage.addBeds(remote, aFacility, deltaACBeds, deltaCCCBeds, deltaLTCBeds);
}

/**
 * Sends an removeBed message
 *
 * @param remote true if the facility that is being changed is this node of EOBC's facility
 * @param aFacility the Facility to add beds to
 * @param deltaACBeds the amount of beds to remove
 * @param deltaCCCBeds the amount of beds to remove
 * @param deltaLTCBeds the amount of beds to remove
 */
void SendChangeDataInterface::removeBeds(bool remote, Facility* aFacility, int deltaACBeds, int deltaCCCBeds, int deltaLTCBeds)
{
    _sendMessage.removeBeds(remote, aFacility, deltaACBeds, deltaCCCBeds, deltaLTCBeds);
}
void SendChangeDataInterface::addFacilities(bool remote,ID id, Facility* aFacility)
{
    _sendMessage.addFacilities(remote,id ,aFacility);
}

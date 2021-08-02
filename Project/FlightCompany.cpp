#include <iostream>
#include <string.h>
using namespace std;

#include "FlightCompany.h"

CFlightCompany::CFlightCompany(const char* name)
{
	setName(name);
}

CFlightCompany::CFlightCompany(const CFlightCompany& cFlightCompany)
{
	setName(cFlightCompany.name);
}

CFlightCompany::~CFlightCompany()
{
	delete[] this->name;
}

char* CFlightCompany::getName()
{
	return this->name;
}

void CFlightCompany::setName(const char* name)
{
	this->name = _strdup(name);
}

void CFlightCompany::print(ostream& out) const
{
	out << "Flight company: " << this->name << endl;
}

const CFlightCompany& CFlightCompany::operator=(const CFlightCompany& other)
{
	if (this != &other)
	{
		delete[] this->name;
		this->name = _strdup(other.name);
	}

	return *this;
}

bool CFlightCompany::addCrewMember(const CCrewMember& pCmArr)
{
	if (this->currentCrew >= CFlightCompany::MAX_CREWS)
		return false;

	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i].isEqual(pCmArr))
			return false;
	}

	this->crewMembers[this->currentCrew++] = pCmArr;
	return true;
}

bool CFlightCompany::addPlane(const CPlane& pPlaneArr)
{
	if (this->currentPlanes >= CFlightCompany::MAX_PLANES)
		return false;

	for (int i = 0; i < this->currentPlanes; i++)
	{
		if (this->planes[i].isEqual(pPlaneArr))
			return false;
	}

	this->planes[this->currentPlanes++] = pPlaneArr;
	return true;
}

bool CFlightCompany::addFlight(const Flight& fArr)
{
	if (fArr.getCurrentCrew() != 0 || this->currentFlights >= CFlightCompany::MAX_FLIGHT)
		return false;

	for (int i = 0; i < this->currentFlights; i++)
	{
		if (this->flights[i] == fArr)
			return false;
	}

	this->flights[this->currentFlights++] = fArr;
	return true;
}

CCrewMember* CFlightCompany::getCrewMember(int workerId)
{
	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i].getWorkerId() == workerId)
			return &this->crewMembers[i];
	}

	return nullptr;
}

const Flight* CFlightCompany::getFlight(int fNum)
{
	for (int i = 0; i < this->currentFlights; i++)
	{
		if (this->flights[i].getFlightInfo().getFNum() == fNum)
			return &this->flights[i];
	}

	return nullptr;
}

void CFlightCompany::addCrewToFlight(int fNum, int workerId)
{
	const Flight& flight = *getFlight(fNum);
	flight + *getCrewMember(workerId);
}

CPlane* CFlightCompany::getPlane(int id)
{
	for (int i = 0; i < currentPlanes; i++)
	{
		if (this->planes[i].getId() == id)
			return &this->planes[i];
	}

	return nullptr;
}
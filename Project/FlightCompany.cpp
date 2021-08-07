#include <iostream>
#include <string.h>
using namespace std;

#include "FlightCompany.h"

CFlightCompany::CFlightCompany(const char* name)
{
	setName(name);
	this->crewMembers = new CCrewMember*[MAX_CREWS];
	this->planes = new CPlane*[MAX_PLANES];
	this->flights = new Flight*[MAX_FLIGHT];
	this->currentCrew = 0;
	this->currentPlanes = 0;
	this->currentFlights = 0;
}

CFlightCompany::~CFlightCompany()
{
	for (int i = 0; i < currentCrew; i++)
		delete this->crewMembers[i];
	delete[] this->crewMembers;

	for (int i = 0; i < currentPlanes; i++)
		delete this->planes[i];
	delete[] this->planes;

	for (int i = 0; i < currentFlights; i++)
		delete this->flights[i];
	delete[] this->flights;

	delete[] this->name;
}

const char* CFlightCompany::getName() const
{
	return this->name;
}

void CFlightCompany::setName(const char* name)
{
	delete[] this->name;
	this->name = _strdup(name);
}

void CFlightCompany::print(ostream& out) const
{
	out << "Flight company: " << this->name << endl;
	out << "There are " << currentCrew << " Crew members: " << endl;
	for (int i = 0; i < currentCrew; i++)
		crewMembers[i]->print(out);
	out << "There are " << currentPlanes << " Planes: " << endl;
	for (int i = 0; i < currentPlanes; i++)
		planes[i]->print(out);
	out << "There are " << currentFlights << " Flights: " << endl;
	for (int i = 0; i < currentFlights; i++)
		out << *flights[i];
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
		if (this->crewMembers[i]->isEqual(pCmArr))
			return false;
	}

	this->crewMembers[this->currentCrew++] = new CCrewMember(pCmArr);
	return true;
}

bool CFlightCompany::addPlane(const CPlane& pPlane)
{
	if (this->currentPlanes >= CFlightCompany::MAX_PLANES)
		return false;

	for (int i = 0; i < this->currentPlanes; i++)
	{
		if (this->planes[i]->isEqual(pPlane))
			return false;
	}

	this->planes[this->currentPlanes++] = new CPlane(pPlane);
	return true;
}

bool CFlightCompany::addFlight(const Flight& flight)
{
	if (flight.getCurrentCrew() != 0 || this->currentFlights >= CFlightCompany::MAX_FLIGHT)
		return false;

	for (int i = 0; i < this->currentFlights; i++)
	{
		if (this->flights[i] == &flight)
			return false;
	}

	this->flights[this->currentFlights++] = new Flight(flight);
	return true;
}

CCrewMember* CFlightCompany::getCrewMember(int workerId)
{
	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i]->getWorkerId() == workerId)
			return this->crewMembers[i];
	}

	return nullptr;
}

Flight* CFlightCompany::getFlight(int fNum)
{
	for (int i = 0; i < this->currentFlights; i++)
	{
		if (this->flights[i]->getFlightInfo().getFNum() == fNum)
			return this->flights[i];
	}

	return nullptr;
}

void CFlightCompany::addCrewToFlight(int fNum, int workerId)
{
	Flight* flight = getFlight(fNum);
	CCrewMember* temp = getCrewMember(workerId);
	*flight + *temp;
}

CPlane* CFlightCompany::getPlane(int index)
{
	if (index < 0 || index >= currentPlanes)
		return nullptr;
	return new CPlane(*this->planes[index]);
}
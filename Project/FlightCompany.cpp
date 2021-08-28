#include <iostream>
#include <string.h>
using namespace std;

#include "FlightCompany.h"

CFlightCompany::CFlightCompany(const char* name)
{
	setName(name);
	this->crewMembers = new CCrewMember*[MAX_CREWS];
	this->planes = new CPlane*[MAX_PLANES];
	this->flights = new CFlight*[MAX_FLIGHT];
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

bool CFlightCompany::addCrewMember(const CCrewMember& pCrewMember)
{
	if (this->currentCrew >= CFlightCompany::MAX_CREWS)
		return false;

	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i]->isEqual(pCrewMember))
			return false;
	}

	const CPilot *p = dynamic_cast<const CPilot*>(&pCrewMember);
	if (p)
		this->crewMembers[this->currentCrew++] = new CPilot(*p);
	const CHost *p1 = dynamic_cast<const CHost*>(&pCrewMember);
	if (p1)
		this->crewMembers[this->currentCrew++] = new CHost(*p1);
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

	const CCargo *p = dynamic_cast<const CCargo*>(&pPlane);
	if (p)
		this->planes[this->currentPlanes++] = new CCargo(*p);
	else
		this->planes[this->currentPlanes++] = new CPlane(pPlane);
	return true;
}

bool CFlightCompany::addFlight(const CFlight& flight)
{
	if (flight.getCurrentCrew() != 0 || this->currentFlights >= CFlightCompany::MAX_FLIGHT)
		return false;

	for (int i = 0; i < this->currentFlights; i++)
	{
		if (*this->flights[i] == flight)
			return false;
	}

	this->flights[this->currentFlights++] = new CFlight(flight);
	return true;
}

CCrewMember* CFlightCompany::getCrewMember(int index)
{
	if (index >= this->currentCrew)
		return nullptr;

	return this->crewMembers[index];
}

CFlight* CFlightCompany::getFlightByNum(int fNum)
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
	CFlight* cFlight = getFlightByNum(fNum);
	CCrewMember* temp = getCrewMember(workerId);
	*cFlight + temp;
}

CPlane* CFlightCompany::getPlane(int index)
{
	if (index < 0 || index >= currentPlanes)
		return nullptr;

	return this->planes[index];
}

int CFlightCompany::getCargoCount() const
{
	int cargoCount = 0;

	for (int i = 0; i < this->currentPlanes; i++)
	{
		if (typeid(*this->planes[i]) == typeid(CCargo))
			cargoCount++;
	}

	return cargoCount;
}

void CFlightCompany::pilotsToSimulator() const
{
	CPilot *cPilot = nullptr;

	for (int i = 0; i < this->currentCrew; i++)
	{
		cPilot = dynamic_cast<CPilot*>(this->crewMembers[i]);
		if (cPilot)
			cPilot->toSimulator();
	}
}

void CFlightCompany::crewGetPresent() const
{
	for (int i = 0; i < this->currentCrew; i++)
		this->crewMembers[i]->getPresent();
}

void CFlightCompany::crewGetUniform() const
{
	for (int i = 0; i < this->currentCrew; i++)
		this->crewMembers[i]->getUniform();
}

bool CFlightCompany::takeOff(int fNum)
{
	return getFlightByNum(fNum)->takeOff();
}
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

CFlightCompany::CFlightCompany(const char* fileName, int file)
{
	ifstream inFile(fileName);
	inFile >> *this;
}

CFlightCompany::~CFlightCompany()
{
	delete[] this->name;

	for (int i = 0; i < currentCrew; i++)
		delete this->crewMembers[i];
	delete[] this->crewMembers;

	for (int i = 0; i < currentPlanes; i++)
		delete this->planes[i];
	delete[] this->planes;

	for (int i = 0; i < currentFlights; i++)
		delete this->flights[i];
	delete[] this->flights;
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

void CFlightCompany::print(ostream& out) const throw(CCompStringException)
{
	if (!this->name)
		throw("There is no flight company name");

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

bool CFlightCompany::addCrewMember(const CCrewMember& pCrewMember)
{
	const CPilot *cPilot = dynamic_cast<const CPilot*>(&pCrewMember);
	const CHost *cHost = dynamic_cast<const CHost*>(&pCrewMember);

	if (this->currentCrew >= CFlightCompany::MAX_CREWS)
		return false;

	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i]->isEqual(pCrewMember))
			return false;
	}

	if (cPilot)
		this->crewMembers[this->currentCrew++] = new CPilot(*cPilot);
	else if (cHost)
		this->crewMembers[this->currentCrew++] = new CHost(*cHost);

	return true;
}

bool CFlightCompany::addPlane(const CPlane& pPlane)
{
	const CCargo *cCargo = dynamic_cast<const CCargo*>(&pPlane);

	if (this->currentPlanes >= CFlightCompany::MAX_PLANES)
		return false;

	for (int i = 0; i < this->currentPlanes; i++)
	{
		if (this->planes[i]->isEqual(pPlane))
			return false;
	}

	if (cCargo)
		this->planes[this->currentPlanes++] = new CCargo(*cCargo);
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

int CFlightCompany::getCrewCount() const
{
	return this->currentCrew;
}

void CFlightCompany::saveToFile(const char* fileName) throw(CCompFileException)
{

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

CPlane& CFlightCompany::operator[](int index) throw(CCompLimitException)
{
	if (index >= this->currentPlanes)
		throw(MAX_PLANES);

	return *this->planes[index];
}

istream& operator>>(istream& in, CFlightCompany& cFlightCompany)
{
	if (typeid(in) == typeid(ifstream))
	{
		in >> cFlightCompany.name;

		in >> cFlightCompany.currentCrew;
		for (int i = 0; i < cFlightCompany.currentCrew; i++)
			in >> *cFlightCompany.crewMembers[i];

		in >> cFlightCompany.currentPlanes;
		for (int i = 0; i < cFlightCompany.currentPlanes; i++)
			in >> *cFlightCompany.planes[i];

		in >> cFlightCompany.currentFlights;
		for (int i = 0; i < cFlightCompany.currentFlights; i++)
			in >> *cFlightCompany.flights[i];
	}
	else
	{
		// 
	}

}
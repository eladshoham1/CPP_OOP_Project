#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string.h>
using namespace std;

#include "FlightCompany.h"
#include "PlaneCrewFactory.h"

CFlightCompany::CFlightCompany(const char* name) throw(CCompStringException)
{
	setName(name);
	this->currentCrew = 0;
	this->currentPlanes = 0;
	this->currentFlights = 0;
}

CFlightCompany::CFlightCompany(const char* fileName, int file) throw(CCompFileException)
{
	ifstream inFile(fileName);

	if (inFile.fail() || inFile.peek() == EOF)
		throw CCompFileException(fileName);

	inFile >> *this;
	inFile.close();
}

CFlightCompany::~CFlightCompany()
{
	delete[] this->name;

	for (int i = 0; i < currentCrew; i++)
		delete this->crewMembers[i];

	for (int i = 0; i < currentPlanes; i++)
		delete this->planes[i];

	for (int i = 0; i < currentFlights; i++)
		delete this->flights[i];
}

const char* CFlightCompany::getName() const
{
	return this->name;
}

int CFlightCompany::getCurrentCrew() const
{
	return this->currentCrew;
}

int CFlightCompany::getCurrentPlanes() const
{
	return this->currentPlanes;
}

int CFlightCompany::getCurrentFlights() const
{
	return this->currentFlights;
}

void CFlightCompany::setName(const char* name) throw(CCompStringException)
{
	if (strcmp(name, "") == 0)
		throw CCompStringException("Name can't be empty");

	delete[] this->name;
	this->name = _strdup(name);
}

void CFlightCompany::print(ostream& out) const
{
	out << *this;
}

void CFlightCompany::addCrewMember(const CCrewMember& pCrewMember) throw(CFlightCompException)
{
	const CPilot *cPilot = dynamic_cast<const CPilot*>(&pCrewMember);
	const CHost *cHost = dynamic_cast<const CHost*>(&pCrewMember);

	if (this->currentCrew >= CFlightCompany::MAX_CREWS)
		throw CCompLimitException(CFlightCompany::MAX_CREWS);

	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i]->isEqual(pCrewMember))
			throw CCompStringException("This crew member already in the flight company");
	}

	if (cPilot)
		this->crewMembers[this->currentCrew++] = new CPilot(*cPilot);
	else if (cHost)
		this->crewMembers[this->currentCrew++] = new CHost(*cHost);
}

void CFlightCompany::addPlane(const CPlane& pPlane) throw(CFlightCompException)
{
	const CCargo *cCargo = dynamic_cast<const CCargo*>(&pPlane);

	if (this->currentPlanes >= CFlightCompany::MAX_PLANES)
		throw CCompLimitException(CFlightCompany::MAX_PLANES);

	for (int i = 0; i < this->currentPlanes; i++)
	{
		if (this->planes[i]->isEqual(pPlane))
			throw CCompStringException("This plane already in the flight company");
	}

	if (cCargo)
		this->planes[this->currentPlanes++] = new CCargo(*cCargo);
	else
		this->planes[this->currentPlanes++] = new CPlane(pPlane);
}

void CFlightCompany::addFlight(const CFlight& flight) throw(CFlightCompException)
{
	if (flight.getCurrentCrew() != 0 || this->currentFlights >= CFlightCompany::MAX_FLIGHT)
		throw CCompLimitException(CFlightCompany::MAX_FLIGHT);

	for (int i = 0; i < this->currentFlights; i++)
	{
		if (*this->flights[i] == flight)
			throw CCompStringException("This flight already in the flight company");
	}
	
	this->flights[this->currentFlights++] = new CFlight(flight);
}

CCrewMember* CFlightCompany::getCrewMember(int index) throw(CCompLimitException)
{
	if (index < 0 || index >= this->currentCrew)
		throw CCompLimitException(this->currentCrew);

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
	ofstream outFile(fileName, ios::trunc);

	if (outFile.fail())
		throw CCompFileException(fileName);

	outFile << *this;
	outFile.close();
}

const CFlightCompany& CFlightCompany::operator=(const CFlightCompany& other)
{
	if (this != &other)
	{
		delete[] this->name;
		this->name = _strdup(other.name);
		this->currentCrew = other.currentCrew;
		this->currentPlanes = other.currentPlanes;
		this->currentFlights = other.currentFlights;

		for (int i = 0; i < this->currentCrew; i++)
			this->addCrewMember(*other.crewMembers[i]);

		for (int i = 0; i < this->currentPlanes; i++)
			this->addPlane(*other.planes[i]);

		for (int i = 0; i < this->currentFlights; i++)
			this->addFlight(*other.flights[i]);
	}

	return *this;
}

CPlane& CFlightCompany::operator[](int index) throw(CCompLimitException)
{
	if (index >= this->currentPlanes)
		throw CCompLimitException(this->currentPlanes);

	return *this->planes[index];
}

ostream& operator<<(ostream& os, const CFlightCompany& cFlightCompany)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << strlen(cFlightCompany.name) << " " << cFlightCompany.name << endl;

		os << cFlightCompany.currentCrew << endl;
		for (int i = 0; i < cFlightCompany.currentCrew; i++)
			os << CPlaneCrewFactory::getCrewType(cFlightCompany.crewMembers[i]) << " " << *cFlightCompany.crewMembers[i];

		os << cFlightCompany.currentPlanes << endl;
		os << CPlane::generateNumber << endl;
		for (int i = 0; i < cFlightCompany.currentPlanes; i++)
			os << CPlaneCrewFactory::getPlaneType(cFlightCompany.planes[i]) << " " << *cFlightCompany.planes[i];

		os << cFlightCompany.currentFlights << endl;
		for (int i = 0; i < cFlightCompany.currentFlights; i++)
			os << *cFlightCompany.flights[i];
	}
	else
	{
		os << "Flight company: " << cFlightCompany.name << endl;
		os << "There are " << cFlightCompany.currentCrew << " Crew members: " << endl;
		for (int i = 0; i < cFlightCompany.currentCrew; i++)
			cFlightCompany.crewMembers[i]->print(os);
		os << "There are " << cFlightCompany.currentPlanes << " Planes: " << endl;
		for (int i = 0; i < cFlightCompany.currentPlanes; i++)
			cFlightCompany.planes[i]->print(os);
		os << "There are " << cFlightCompany.currentFlights << " Flights: " << endl;
		for (int i = 0; i < cFlightCompany.currentFlights; i++)
			cFlightCompany.flights[i]->print(os);
	}

	return os;
}

istream& operator>>(istream& in, CFlightCompany& cFlightCompany)
{
	if (typeid(in) == typeid(ifstream))
	{
		ifstream& inFile = dynamic_cast<ifstream&>(in);
		int nameLen;
		in >> nameLen;

		delete[] cFlightCompany.name;
		cFlightCompany.name = new char[nameLen];
		in >> cFlightCompany.name;

		in >> cFlightCompany.currentCrew;
		for (int i = 0; i < cFlightCompany.currentCrew; i++)
			cFlightCompany.crewMembers[i] = CPlaneCrewFactory::getCrewMemberFromFile(inFile);

		in >> cFlightCompany.currentPlanes;
		in >> CPlane::generateNumber;
		for (int i = 0; i < cFlightCompany.currentPlanes; i++)
			cFlightCompany.planes[i] = CPlaneCrewFactory::getPlaneFromFile(inFile);

		in >> cFlightCompany.currentFlights;
		for (int i = 0; i < cFlightCompany.currentFlights; i++)
			cFlightCompany.flights[i] = new CFlight(inFile);
	}
	else
		CPlaneCrewFactory::getCompanyDataFromUser(cFlightCompany);

	return in;
}
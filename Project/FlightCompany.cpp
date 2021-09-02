#include <fstream>
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

	this->name = new char[MAX_SIZE];
	inFile >> this->name;
	inFile >> this->currentCrew;
	this->crewMembers = new CCrewMember*[CFlightCompany::MAX_CREWS];
	for (int i = 0; i < this->currentCrew; i++)
	{
		int type;
		inFile >> type;
		if (type == 0)
			this->crewMembers[i] = new CHost(inFile);
		else
			this->crewMembers[i] = new CPilot(inFile);
	}

	inFile >> this->currentPlanes;
	this->planes = new CPlane*[CFlightCompany::MAX_PLANES];
	for (int i = 0; i < this->currentPlanes; i++)
	{
		int type;
		inFile >> type;

		if (type == 0)
			this->planes[i] = new CPlane(inFile);
		else
			this->planes[i] = new CCargo(inFile);
	}

	inFile >> this->currentFlights;
	this->flights = new CFlight*[CFlightCompany::MAX_FLIGHT];
	for (int i = 0; i < this->currentFlights; i++)
		this->flights[i] = new CFlight(inFile);

	//inFile >> *this;
	inFile.close();
}

CFlightCompany::CFlightCompany(const CFlightCompany& cFlightCompany)
{
	*this = cFlightCompany;
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

	out << *this;
	/*out << "Flight company: " << this->name << endl;
	out << "There are " << currentCrew << " Crew members: " << endl;
	for (int i = 0; i < currentCrew; i++)
		crewMembers[i]->print(out);
	out << "There are " << currentPlanes << " Planes: " << endl;
	for (int i = 0; i < currentPlanes; i++)
		planes[i]->print(out);
	out << "There are " << currentFlights << " Flights: " << endl;
	for (int i = 0; i < currentFlights; i++)
		out << *flights[i];*/
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
	ofstream outFile(fileName);

}

const CFlightCompany& CFlightCompany::operator=(const CFlightCompany& other)
{
	if (this != &other)
	{
		delete[] this->name;
		this->name = _strdup(other.name);
		// need to expand!!!!
	}

	return *this;
}

CPlane& CFlightCompany::operator[](int index) throw(CCompLimitException)
{
	if (index >= this->currentPlanes)
		throw(MAX_PLANES);

	return *this->planes[index];
}

ostream& operator<<(ostream os, const CFlightCompany& cFlightCompany)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << cFlightCompany.name << endl;

		os << cFlightCompany.currentCrew << endl;
		for (int i = 0; i < cFlightCompany.currentCrew; i++)
			os << *cFlightCompany.crewMembers[i];

		os << cFlightCompany.currentPlanes << endl;
		for (int i = 0; i < cFlightCompany.currentPlanes; i++)
			os << *cFlightCompany.planes[i];

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
			os << *cFlightCompany.flights[i]; // to change to print -> cFlightCompany.flights[i]->print(os); (print in flight)
	}

	return os;
}

istream& operator>>(istream& in, CFlightCompany& cFlightCompany)
{

	if (typeid(in) == typeid(ifstream))
	{
		ifstream *inFile = dynamic_cast<ifstream*>(&in);
		int type;
		in >> type;

		delete[] cFlightCompany.name;
		cFlightCompany.name = new char[MAX_SIZE];
		in >> cFlightCompany.name;

		in >> cFlightCompany.currentCrew;
		cFlightCompany.crewMembers = new CCrewMember*[CFlightCompany::MAX_CREWS];
		for (int i = 0; i < cFlightCompany.currentCrew; i++)
		{
			if (type == 0)
				cFlightCompany.crewMembers[i] = new CHost(*inFile);
			else
				cFlightCompany.crewMembers[i] = new CPilot(*inFile);
		}

		in >> cFlightCompany.currentPlanes;
		for (int i = 0; i < cFlightCompany.currentPlanes; i++)
		{
			if (type == 0)
				cFlightCompany.planes[i] = new CPlane(*inFile);
			else
				cFlightCompany.planes[i] = new CCargo(*inFile);
		}

		in >> cFlightCompany.currentFlights;
		for (int i = 0; i < cFlightCompany.currentFlights; i++)
			cFlightCompany.flights[i] = new CFlight(*inFile);
	}
	else
	{
		//
	}

	return in;
}
#include <fstream>
using namespace std;
#include <string.h>

#include "Flight.h"

CFlight::CFlight(CFlightInfo flightInfo, CPlane* plane) : flightInfo(flightInfo)
{
	setPlane(plane);
	this->crewMembers = new CCrewMember*[CFlight::MAX_CREW];
	this->currentCrew = 0;
}

CFlight::CFlight(ifstream& in) : flightInfo(in)
{
	in >> *this;
}

CFlight::CFlight(const CFlight& cFlight) : flightInfo(cFlight.flightInfo)
{
	*this = cFlight;
}

CFlight::~CFlight()
{
	delete this->plane;
}

const CFlightInfo& CFlight::getFlightInfo() const
{
	return this->flightInfo;
}

CPlane* CFlight::getPlane() const
{
	return this->plane;
}

int CFlight::getCurrentCrew() const
{
	return this->currentCrew;
}

void CFlight::setPlane(CPlane* plane)
{
	CCargo *cCargo = dynamic_cast<CCargo*>(plane);
	
	if (cCargo)
		this->plane = new CCargo(*cCargo);
	else
		this->plane = new CPlane(*plane);
}

bool CFlight::checkPlane() const
{
	CHost *host = nullptr;
	int isOnePilot = 0, isSuperHost = 0;

	for (int i = 0; i < this->currentCrew; i++)
	{
		if (typeid(*this->crewMembers[i]) == typeid(CPilot))
		{
			if (isOnePilot == 1)
				return false;
			isOnePilot = 1;
		}
		else
		{
			host = dynamic_cast<CHost*>(this->crewMembers[i]);
			if (host && host->getHostType() == CHost::eSuper)
			{
				if (isSuperHost == 1)
					return false;
				isSuperHost = 1;
			}
		}
	}

	return isOnePilot == 1;
}

bool CFlight::checkCargo() const
{
	for (int i = 0; i < this->currentCrew; i++)
	{
		if (typeid(*this->crewMembers[i]) == typeid(CPilot))
			return true;
	}

	return false;
}

bool CFlight::takeOff()
{
	int minutes = this->flightInfo.getFlightMinutes();

	if (!this->plane || (typeid(*this->plane) == typeid(CPlane) && !checkPlane()) || 
		(typeid(*this->plane) == typeid(CCargo) && !checkCargo()))
		return false;

	for (int i = 0; i < this->currentCrew; i++)
		this->crewMembers[i]->takeOff(minutes);
	this->plane->takeOff(minutes);

	return true;
}

const CFlight& CFlight::operator=(const CFlight& other)
{
	if (this != &other)
	{
		this->flightInfo = other.flightInfo;
		setPlane(other.plane);
		this->crewMembers = other.crewMembers;
		this->currentCrew = other.currentCrew;
	}

	return *this;
}

CFlight operator+(CFlight& theFlight, CCrewMember* newCrewMember)
{
	if (theFlight.currentCrew >= CFlight::MAX_CREW)
		return theFlight;

	for (int i = 0; i < theFlight.currentCrew; i++)
	{
		if (theFlight.crewMembers[i] == newCrewMember)
			return theFlight;
	}

	theFlight.crewMembers[theFlight.currentCrew++] = newCrewMember;
	return theFlight;
}

CFlight operator+(CCrewMember* cCrewMember, CFlight& theFlight)
{
	return theFlight + cCrewMember;
}

ostream& operator<<(ostream& os, const CFlight& cFlight)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << cFlight.flightInfo << " ";
		
		if (cFlight.plane)
			os << 1 << *cFlight.plane;
		else
			os << 0;

		os << endl << cFlight.currentCrew << endl;
		for (int i = 0; i < cFlight.currentCrew; i++)
			os << *cFlight.crewMembers[i];
	}
	else
	{
		os << "Flight " << cFlight.flightInfo;
		if (cFlight.plane)
			os << *cFlight.plane;
		else
			os << "No plane assign yet";
		os << " There are " << cFlight.currentCrew << " crew members in flight:" << endl;

		for (int i = 0; i < cFlight.currentCrew; i++)
			os << *cFlight.crewMembers[i];
	}

	return os;
}

istream& operator>>(istream& in, CFlight& cFlight)
{
	if (typeid(in) == typeid(ifstream))
	{
		int hasPlane;
		in >> hasPlane;
	
		//if (hasPlane == 1)
			//cFlight.plane = new CPlane(in);
		in >> cFlight.currentCrew;
		for (int i = 0; i < cFlight.currentCrew; i++)
			in >> *cFlight.crewMembers[i];
	}
	else
	{
		//
	}

	return in;
}

bool CFlight::operator==(const CFlight& other) const
{
	return !(this->flightInfo != other.flightInfo);
}
#include <fstream>
using namespace std;
#include <string.h>

#include "Flight.h"
#include "PlaneCrewFactory.h"

CFlight::CFlight(CFlightInfo flightInfo, CPlane* plane) : flightInfo(flightInfo)
{
	setPlane(plane);
	this->currentCrew = 0;
}

CFlight::CFlight(ifstream& in) : flightInfo(in)
{
	in >> *this;
}

CFlight::CFlight(const CFlight& cFlight) throw(CFlightCompException) : flightInfo(cFlight.flightInfo)
{
	*this = cFlight;
}

CFlight::~CFlight()
{
	if (this->plane != nullptr)
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

int CFlight::getPlaneId() const
{
	return this->planeId;
}

void CFlight::setPlane(CPlane* plane)
{
	if (plane != nullptr)
	{
		CCargo *cCargo = dynamic_cast<CCargo*>(plane);
	
		if (cCargo)
			this->plane = new CCargo(*cCargo);
		else
			this->plane = new CPlane(*plane);

		this->planeId = this->plane->getId();
	}
	else
	{
		this->plane = nullptr;
		this->planeId = 0;
	}
}

void CFlight::addCrewMember(const CCrewMember* newCrewMember) throw(CFlightCompException)
{
	if (newCrewMember == nullptr)
		throw CCompStringException("Crew member can't be null");

	if (this->currentCrew >= CFlight::MAX_CREW)
		throw CCompLimitException(CFlight::MAX_CREW);

	for (int i = 0; i < this->currentCrew; i++)
	{
		if (this->crewMembers[i]->isEqual(*newCrewMember))
			throw CCompStringException("This crew member already in this flight");
	}

	const CPilot *pilot = dynamic_cast<const CPilot*>(newCrewMember);
	const CHost *host = dynamic_cast<const CHost*>(newCrewMember);

	if (pilot)
		this->crewMembers[this->currentCrew++] = new CPilot(*pilot);
	else if (host)
		this->crewMembers[this->currentCrew++] = new CHost(*host);
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

void CFlight::print(ostream& out) const
{
	out << *this;
}

const CFlight& CFlight::operator=(const CFlight& other) throw(CFlightCompException)
{
	if (this != &other)
	{
		this->flightInfo = other.flightInfo;
		setPlane(other.plane);
		this->currentCrew = 0;
		for (int i = 0; i < other.currentCrew; i++)
			this->addCrewMember(other.crewMembers[i]);
	}

	return *this;
}

CFlight operator+(CFlight& theFlight, CCrewMember* newCrewMember) throw(CFlightCompException)
{
	theFlight.addCrewMember(newCrewMember);
	return theFlight;
}

CFlight operator+(CCrewMember* cCrewMember, CFlight& theFlight) throw(CFlightCompException)
{
	return theFlight + cCrewMember;
}

ostream& operator<<(ostream& os, const CFlight& cFlight)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << cFlight.flightInfo << " ";
		
		if (cFlight.plane)
			os << 1 << " " << cFlight.planeId;
		else
			os << 0;

		os << endl << cFlight.currentCrew << endl;
		for (int i = 0; i < cFlight.currentCrew; i++)
			os << CPlaneCrewFactory::getCrewType(cFlight.crewMembers[i]) << " " << *cFlight.crewMembers[i];
	}
	else
	{
		os << "Flight " << cFlight.flightInfo;
		if (cFlight.plane)
			os << *cFlight.plane;
		else
			os << "No plane assign yet" << endl;
		os << "There are " << cFlight.currentCrew << " crew members in flight:" << endl;

		for (int i = 0; i < cFlight.currentCrew; i++)
			os << *cFlight.crewMembers[i];
	}

	return os;
}

istream& operator>>(istream& in, CFlight& cFlight)
{
	if (typeid(in) == typeid(ifstream))
	{
		ifstream& inFile = dynamic_cast<ifstream&>(in);
		int hasPlane;
		in >> hasPlane;

		if (hasPlane == 1)
			in >> cFlight.planeId;

		in >> cFlight.currentCrew;
		for (int i = 0; i < cFlight.currentCrew; i++)
			cFlight.crewMembers[i] = CPlaneCrewFactory::getCrewMemberFromFile(inFile);
	}

	return in;
}

bool CFlight::operator==(const CFlight& other) const
{
	return !(this->flightInfo != other.flightInfo);
}
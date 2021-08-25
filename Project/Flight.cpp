#include <iostream>
using namespace std;
#include <string.h>

#include "Flight.h"

CFlight::CFlight(CFlightInfo flightInfo, CPlane* plane) : flightInfo(flightInfo)
{
	setPlane(plane);
	this->crewMembers = new CCrewMember*[CFlight::MAX_CREW];
	this->currentCrew = 0;
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

int CFlight::getCurrentCrew() const
{
	return this->currentCrew;
}

void CFlight::setPlane(CPlane* plane)
{
	if (plane != nullptr)
		this->plane = new CPlane(*plane);
	else
		this->plane = nullptr;
}

bool CFlight::takeOff() const
{
	switch (typeid(this->plane).name)
	{
		case typeid(CPlane).name:

			break;
		case typeid(CCargo).name:

			break;
	}

	return false;
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
	os << "Flight " << cFlight.flightInfo;
	if (cFlight.plane)
		os << *cFlight.plane;
	else
		os << "No plane assign yet";
	os << " There are " << cFlight.currentCrew << " crew members in flight:" << endl;

	for (int i = 0; i < cFlight.currentCrew; i++)
		os << *cFlight.crewMembers[i];

	return os;
}

bool CFlight::operator==(const CFlight& other) const
{
	return !(this->flightInfo != other.flightInfo);
}
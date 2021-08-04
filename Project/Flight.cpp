#include <iostream>
#include <string.h>
using namespace std;

#include "Flight.h"
#include "CrewMember.h"

Flight::Flight(CFlightInfo flightInfo, CPlane* plane) : flightInfo(flightInfo)
{
	if(plane != nullptr)
		this->plane = new CPlane(*plane);
	else
		this->plane = nullptr;
	this->crewMembers = new CCrewMember*[Flight::MAX_CREW];
	this->currentCrew = 0;
}

Flight::Flight(const Flight& cFlight) : flightInfo(cFlight.flightInfo)
{
	if (cFlight.plane != nullptr)
		this->plane = new CPlane(*cFlight.plane);
	else
		this->plane = nullptr;
	this->crewMembers = cFlight.crewMembers;
	this->currentCrew = cFlight.currentCrew;
}

Flight::Flight(Flight&& cFlight) : flightInfo(cFlight.flightInfo)
{
	this->plane = cFlight.plane;
	cFlight.plane = nullptr;
	this->crewMembers = cFlight.crewMembers;
	cFlight.crewMembers = nullptr;
	this->currentCrew = cFlight.currentCrew;
}

Flight::~Flight()
{
	delete this->plane;
	for (int i = 0; i < currentCrew; i++)
		delete crewMembers[i];
	if (this->crewMembers != nullptr)
		delete[] this->crewMembers;
}

const CFlightInfo& Flight::getFlightInfo()
{
	return this->flightInfo;
}

int Flight::getCurrentCrew() const
{
	return this->currentCrew;
}

void Flight::setPlane(CPlane* plane)
{
	this->plane = plane;
}

Flight operator+(Flight& theFlight, CCrewMember& newCrewMember)
{
	if (theFlight.currentCrew >= Flight::MAX_CREW)
		return theFlight;

	for (int i = 0; i < theFlight.currentCrew; i++)
	{
		if (theFlight.crewMembers[i] == &newCrewMember)
			return theFlight;
	}

	theFlight.crewMembers[theFlight.currentCrew++] = &newCrewMember;
	return theFlight;
}

Flight operator+(CCrewMember& cCrewMember, Flight& theFlight)
{
	return theFlight + cCrewMember;
}

ostream& operator<<(ostream& os, const Flight& cFlight)
{
	os << "Flight " << cFlight.flightInfo;
	if (cFlight.plane)
		os << *cFlight.plane << " ";
	else
		os << "No plane assign yet ";
	os<< "There are " << cFlight.currentCrew << " crew members in flight:"<<endl;

	for (int i = 0; i < cFlight.currentCrew; i++)
		os << cFlight.crewMembers[i] << endl;

	return os;
}

bool Flight::operator==(const Flight& other) const
{
	return !(this->flightInfo != other.flightInfo);
}
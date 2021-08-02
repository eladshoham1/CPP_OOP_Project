#include <iostream>
#include <string.h>
using namespace std;

#include "Flight.h"
#include "CrewMember.h"

Flight::Flight(CFlightInfo flightInfo, CPlane* plane) : flightInfo(flightInfo)
{
	this->plane = plane;
	this->crewMembers = new CCrewMember*[Flight::MAX_CREW];
}

Flight::Flight(const Flight& cFlight) : flightInfo(cFlight.flightInfo)
{
	this->plane = cFlight.plane;
	this->crewMembers = cFlight.crewMembers;
	this->currentCrew = cFlight.currentCrew;
}

Flight::~Flight()
{
	delete this->plane;
	delete[] this->crewMembers;
}

void Flight::setPlane(CPlane* plane)
{
	this->plane = plane;
}

Flight operator+(const Flight& theFlight, CCrewMember& newCrewMember)
{
	if (theFlight.currentCrew >= Flight::MAX_CREW)
		return theFlight;

	for (int i = 0; i < theFlight.currentCrew; i++)
	{
		if (theFlight.crewMembers[i] == &newCrewMember)
			return theFlight;
	}

	Flight temp(theFlight);
	temp.crewMembers[temp.currentCrew++] = &newCrewMember;

	return temp;
}

Flight operator+(CCrewMember& cCrewMember, const Flight& theFlight)
{
	return theFlight + cCrewMember;
}

ostream& operator<<(ostream& os, const Flight& cFlight)
{
	os << "Flight " << cFlight.flightInfo << cFlight.plane << endl << "There are " << cFlight.currentCrew << "crew members in flight:";

	for (int i = 0; i < cFlight.currentCrew; i++)
		os << cFlight.crewMembers[i] << endl;

	return os;
}

bool Flight::operator==(const Flight& other) const
{
	return !(this->flightInfo != other.flightInfo);
}
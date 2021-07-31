#include <iostream>
#include <string.h>
using namespace std;

#include "Flight.h"
#include "CrewMember.h"

Flight::Flight(CFlightInfo flightInfo, CPlane* plane) : flightInfo(flightInfo)
{
	this->plane = plane;
	this->crewMembers = new CCrewMember[MAX_CREW];
}

Flight::Flight(const Flight& flight)
{

}

Flight::~Flight()
{

}

void Flight::setPlane(CPlane* plane)
{

}

Flight operator+(const CCrewMember& cCrewMember)
{

}

ostream& operator<<(ostream& os, const Flight& cAddress)
{

}

bool Flight::operator==(const Flight& other) const
{

}
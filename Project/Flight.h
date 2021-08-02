#pragma once
#include "FlightInfo.h"
#include "Plane.h"
#include "CrewMember.h"

class Flight
{
private:
	static constexpr int MAX_CREW = 10;
	CFlightInfo flightInfo;
	CPlane* plane;
	CCrewMember** crewMembers;
	int currentCrew;

public:
	Flight(CFlightInfo flightInfo, CPlane* plane=nullptr);
	Flight(const Flight& cFlight);
	~Flight();

	void setPlane(CPlane* plane);
	friend Flight operator+(const Flight& theFlight, CCrewMember& cCrewMember);
	friend Flight operator+(CCrewMember& cCrewMember, const Flight& theFlight);
	friend ostream& operator<<(ostream& os, const Flight& cFlight);
	bool operator==(const Flight& other) const;
};


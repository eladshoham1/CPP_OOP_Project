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
	CCrewMember* crewMembers;
	int currentCrew;

public:
	Flight(CFlightInfo flightInfo, CPlane* plane=nullptr);
	Flight(const Flight& flight);
	~Flight();

	void setPlane(CPlane* plane);
	friend Flight operator+(const CCrewMember& cCrewMember);
	friend ostream& operator<<(ostream& os, const Flight& cAddress);
	bool operator==(const Flight& other) const;
};


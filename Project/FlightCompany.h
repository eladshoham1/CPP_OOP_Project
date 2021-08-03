#pragma once
#include "CrewMember.h"
#include "Plane.h"
#include "Flight.h"

class CFlightCompany
{
private:
	static constexpr int MAX_CREWS = 10;
	static constexpr int MAX_PLANES = 10;
	static constexpr int MAX_FLIGHT = 10;
	char* name;
	CCrewMember** crewMembers;
	CPlane** planes;
	Flight** flights;
	int currentCrew;
	int currentPlanes;
	int currentFlights;

public:
	CFlightCompany(const char* name);
	CFlightCompany(const CFlightCompany& cFlightCompany);
	~CFlightCompany();

	char* getName();
	void setName(const char* name);

	void print(ostream& out) const;

	const CFlightCompany& operator=(const CFlightCompany& other);
	bool addCrewMember(const CCrewMember& pCmArr);
	bool addPlane(const CPlane& pPlaneArr);
	bool addFlight(const Flight& fArr);
	CCrewMember* getCrewMember(int workerId);
	const Flight* getFlight(int fNum);
	void addCrewToFlight(int fNum, int workerId);
	CPlane* getPlane(int index);
};


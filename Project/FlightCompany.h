#pragma once
#include <iostream>
using namespace std;

#include "CrewMember.h"
#include "Plane.h"
#include "Flight.h"
#include "Pilot.h"

class CFlightCompany
{
private:
	static constexpr int MAX_CREWS = 10;
	static constexpr int MAX_PLANES = 10;
	static constexpr int MAX_FLIGHT = 10;
	char* name;
	CCrewMember** crewMembers;
	CPlane** planes;
	CFlight** flights;
	int currentCrew;
	int currentPlanes;
	int currentFlights;

public:
	CFlightCompany(const char* name);
	CFlightCompany(const CFlightCompany& cFlightCompany) = delete;
	~CFlightCompany();

	const char* getName() const;

	void setName(const char* name);

	void print(ostream& out) const;

	const CFlightCompany& operator=(const CFlightCompany& other);
	bool addCrewMember(const CCrewMember& pCmArr);
	bool addPlane(const CPlane& pPlaneArr);
	bool addFlight(const CFlight& fArr);
	CCrewMember* getCrewMember(int workerId);
	CFlight* getFlightByNum(int fNum);
	void addCrewToFlight(int fNum, int workerId);
	CPlane* getPlane(int index);

	int getCargoCount() const;
	void pilotsToSimulator() const;
	void crewGetPresent() const;
	void crewGetUniform() const;
	bool takeOff(int fNum);
};
#pragma once

#include "FlightInfo.h"
#include "Plane.h"
#include "Cargo.h"
#include "CrewMember.h"
#include "Pilot.h"
#include "Host.h"

class CFlight
{
private:
	static constexpr int MAX_CREW = 10;
	CFlightInfo flightInfo;
	CPlane* plane;
	CCrewMember** crewMembers;
	int currentCrew;

public:
	CFlight(CFlightInfo flightInfo, CPlane* plane = nullptr);
	CFlight(const CFlight& cFlight);
	~CFlight();

	const CFlightInfo& getFlightInfo() const;
	CPlane* getPlane() const;
	int getCurrentCrew() const;

	void setPlane(CPlane* plane);

	bool checkPlane() const;
	bool checkCargo() const;
	virtual bool takeOff();

	const CFlight& operator=(const CFlight& other);
	friend CFlight operator+(CFlight& theFlight, CCrewMember* cCrewMember);
	friend CFlight operator+(CCrewMember* cCrewMember, CFlight& theFlight);
	friend ostream& operator<<(ostream& os, const CFlight& cFlight);
	bool operator==(const CFlight& other) const;
};
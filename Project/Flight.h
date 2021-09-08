#pragma once
#pragma warning(disable : 4290)

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
	CCrewMember* crewMembers[MAX_CREW];
	int currentCrew;
	int planeId;

public:
	CFlight(CFlightInfo flightInfo, CPlane* plane = nullptr);
	CFlight(ifstream& in);
	CFlight(const CFlight& cFlight);
	~CFlight();

	const CFlightInfo& getFlightInfo() const;
	CPlane* getPlane() const;
	int getCurrentCrew() const;
	int getPlaneId() const;

	void setPlane(CPlane* plane);

	bool checkPlane() const;
	bool checkCargo() const;
	virtual bool takeOff();
	void print(ostream& out) const;

	const CFlight& operator=(const CFlight& other);
	friend CFlight operator+(CFlight& theFlight, CCrewMember* cCrewMember) throw(CFlightCompException);
	friend CFlight operator+(CCrewMember* cCrewMember, CFlight& theFlight) throw(CFlightCompException);
	friend ostream& operator<<(ostream& os, const CFlight& cFlight);
	friend istream& operator>>(istream& in, CFlight& cFlight);
	bool operator==(const CFlight& other) const;
};
#pragma once
#include <iostream>
using namespace std;

#include "FlightCompException.h"
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
	CFlightCompany(const char* fileName, int file);
	CFlightCompany(const CFlightCompany& cFlightCompany) = delete;
	~CFlightCompany();

	const char* getName() const;

	void setName(const char* name);

	void print(ostream& out) const;

	bool addCrewMember(const CCrewMember& pCrewMember);
	bool addPlane(const CPlane& pPlaneArr);
	bool addFlight(const CFlight& fArr);
	CCrewMember* getCrewMember(int workerId);
	CFlight* getFlightByNum(int fNum);
	void addCrewToFlight(int fNum, int workerId);

	int getCargoCount() const;
	void pilotsToSimulator() const;
	void crewGetPresent() const;
	void crewGetUniform() const;
	bool takeOff(int fNum);
	int getCrewCount() const;
	void saveToFile(const char* fileName) throw(CCompFileException);

	const CFlightCompany& operator=(const CFlightCompany& other);
	CPlane& operator[](int index) throw(CCompLimitException);
	friend ostream& operator>>(istream& in, const CFlightCompany& cFlightCompany);
};
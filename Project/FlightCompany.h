#pragma once
#pragma warning(disable : 4290)

#include <iostream>
using namespace std;

#include "FlightCompException.h"
#include "CrewMember.h"
#include "Plane.h"
#include "Flight.h"
#include "Pilot.h"

#define MAX_SIZE 100

class CFlightCompany
{
private:
	static constexpr int MAX_CREWS = 10;
	static constexpr int MAX_PLANES = 10;
	static constexpr int MAX_FLIGHT = 10;
	char* name;
	CCrewMember* crewMembers[MAX_CREWS];
	CPlane* planes[MAX_PLANES];
	CFlight* flights[MAX_FLIGHT];
	int currentCrew;
	int currentPlanes;
	int currentFlights;

public:
	CFlightCompany(const char* name) throw(CCompStringException);
	CFlightCompany(const char* fileName, int file) throw(CCompFileException);
	CFlightCompany(const CFlightCompany& cFlightCompany) = delete;
	~CFlightCompany();

	const char* getName() const;
	int getCurrentCrew() const;
	int getCurrentPlanes() const;
	int getCurrentFlights() const;

	void setName(const char* name) throw(CCompStringException);

	void print(ostream& out) const;
	void addCrewMember(const CCrewMember& pCrewMember) throw(CFlightCompException);
	void addPlane(const CPlane& pPlaneArr) throw(CFlightCompException);
	void addFlight(const CFlight& fArr) throw(CFlightCompException);
	CCrewMember* getCrewMember(int workerId) throw(CCompStringException);
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
	friend ostream& operator<<(ostream& os, const CFlightCompany& cFlightCompany);
	friend istream& operator>>(istream& in, CFlightCompany& cFlightCompany);
};
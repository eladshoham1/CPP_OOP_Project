#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;

#include "Plane.h"
#include "Cargo.h"
#include "Host.h"
#include "Pilot.h"
#include "Flight.h"

typedef enum PlaneType
{
	eRegular,
	eCargo,
	nofPlaneType
};

typedef enum CrewType
{
	eHost,
	ePilot,
	nofCrewType
};

const string planeType_TITLE[nofPlaneType] = { "Regular", "Cargo" };
const string crewType_TITLE[nofCrewType] = { "Host", "Pilot" };

class CPlane;
class CCrewMember;
class CFlightCompany;
class CAddress;

class CPlaneCrewFactory
{
private:
	CPlaneCrewFactory(void) { ; }

public:
	static PlaneType getPlaneType(const CPlane* pPlane);
	static CrewType getCrewType(const CCrewMember* pCrew);
	static void getCompanyDataFromUser(CFlightCompany& comp);
	static CAddress* getAddressFromUser();
	static CPlane* getPlaneFromUser();
	static CCrewMember* getCrewFromUser();
	static CFlight* getFlightFromUser();

	static CCrewMember* getCrewMemberFromFile(ifstream& inFile);
	static CPlane* getPlaneFromFile(ifstream& inFile);
};

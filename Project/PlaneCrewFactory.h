#pragma once
#pragma warning(disable : 4290)
#define _CRT_SECURE_NO_WARNINGS

#include <string>
using namespace std;

#include "FlightCompany.h"

enum planeType { eRegular, eCargo, nofPlaneType };
enum crewType { eHost, ePilot, nofCrewType };

const string planeTypeTitle[nofPlaneType] = { "Regular", "Cargo" };
const string crewTypeTitle[nofCrewType] = { "Host", "Pilot" };

class CPlaneCrewFactory
{
public:

	static planeType getPlaneType(const CPlane* pPlane);
	static crewType getCrewType(const CCrewMember* pCrew);
	static void getCompanyDataFromUser(CFlightCompany& comp);
	static CPlane* getPlaneFromUser();
	static CCrewMember* getCrewFromUser();
	static CAddress* getAddressFromUser();
	static void getFlightFromUser(CFlightCompany& comp);

	static CCrewMember* getCrewMemberFromFile(ifstream& inFile);
	static CPlane* getPlaneFromFile(ifstream& inFile);

	static void cleanBuffer();

private:
	CPlaneCrewFactory(void) { ; }
};
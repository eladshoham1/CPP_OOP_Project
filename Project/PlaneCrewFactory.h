#pragma once
#pragma warning(disable : 4290)
#define _CRT_SECURE_NO_WARNINGS

#include <string>
using namespace std;

#include "FlightCompany.h"

enum PlaneType { eRegular, eCargo, nofPlaneType };
enum CrewType { eHost, ePilot, nofCrewType };

const string planeTypeTitle[nofPlaneType] = { "Regular", "Cargo" };
const string crewTypeTitle[nofCrewType] = { "Host", "Pilot" };

class CPlaneCrewFactory
{
public:

	static PlaneType getPlaneType(const CPlane* pPlane);
	static CrewType getCrewType(const CCrewMember* pCrew);
	static void getCompanyDataFromUser(CFlightCompany& comp);
	static CPlane* getPlaneFromUser();
	static CCrewMember* getCrewFromUser();
	static CAddress* getAddressFromUser() throw(CCompStringException);

	static CCrewMember* getCrewMemberFromFile(ifstream& inFile);
	static CPlane* getPlaneFromFile(ifstream& inFile);

	static void cleanBuffer();

private:
	CPlaneCrewFactory(void) { ; }
};
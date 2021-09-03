#pragma once

#include "FlightCompany.h"

enum PlaneType { eRegular, eCargo, nofPlaneType };
enum CrewType { eHost, ePilot, nofCrewType };

const string planeTypeTitle[nofPlaneType] = { "Regular", "Cargo" };
const string crewTypeTitle[nofCrewType] = { "Host", "Pilot" };

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
	static void getFlightFromUser(CFlightCompany& comp);

	static CCrewMember* getCrewMemberFromFile(ifstream& inFile);
	static CPlane* getPlaneFromFile(ifstream& inFile);
	
	static void cleanBuffer();
};

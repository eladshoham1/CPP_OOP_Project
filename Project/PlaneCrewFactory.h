#pragma once


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
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;


const string planeType_TITLE[nofPlaneType] = { "Regular","Cargo" };
const string crewType_TITLE[nofCrewType] = { "Host","Pilot" };


class CPlane;
class CCrewMember;
class CFlightCompany;
class CAddress;

class CPlaneCrewFactory
{
public:

	static PlaneType getPlaneType(const CPlane* pPlane);
	static CrewType getCrewType(const CCrewMember* pCrew);
	static void getCompanyDataFromUser(CFlightCompany& comp);
	static CPlane* getPlaneFromUser();
	static CCrewMember* getCrewFromUser();

	static CCrewMember* getCrewMemberFromFile(ifstream& inFile);
	static CPlane* getPlaneFromFile(ifstream& inFile);


private:
	CPlaneCrewFactory(void) { ; }
};

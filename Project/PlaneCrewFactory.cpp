#include <fstream>
#include "PlaneCrewFactory.h"

PlaneType CPlaneCrewFactory::getPlaneType(const CPlane* pPlane)
{
	if (typeid(*pPlane) == typeid(CPlane))
		return eRegular;
	else if (typeid(*pPlane) == typeid(CCargo))
		return eCargo;

	return nofPlaneType;
}

CrewType CPlaneCrewFactory::getCrewType(const CCrewMember* pCrew)
{
	if (typeid(*pCrew) == typeid(CHost))
		return eHost;
	else if (typeid(*pCrew) == typeid(CPilot))
		return ePilot;

	return nofCrewType;
}

void CPlaneCrewFactory::getCompanyDataFromUser(CFlightCompany& comp)
{
	bool addData;
	CCrewMember* pCrewMember;
	CPlane* pPlane;
	CFlight* pFlight;

	do
	{
		cout << "Add new crew member? (true/false) ";
		cin >> addData;

		if (!addData)
			break;

		pCrewMember = getCrewFromUser();
		comp.addCrewMember(*pCrewMember);
	} while (addData);

	do
	{
		cout << "Add new plane? (true/false) ";
		cin >> addData;

		if (!addData)
			break;

		pPlane = getPlaneFromUser();
		comp.addPlane(*pPlane);
	} while (addData);

	do
	{
		cout << "Add new flight? (true/false) ";
		cin >> addData;

		if (!addData)
			break;

		pFlight = getFlightFromUser();
		comp.addFlight(*pFlight);
	} while (addData);
}

CAddress* CPlaneCrewFactory::getAddressFromUser()
{
	CAddress* cAddress;
	int homeNumber;
	char street[MAX], city[MAX];

	cout << "Please enter home number: ";
	cin >> homeNumber;
	cout << "\nPlease enter street: ";
	cin.getline(street, MAX);
	cout << "\nPlease enter city: ";
	cin.getline(city, MAX);

	cAddress = new CAddress(homeNumber, street, city);
	return cAddress;
}

CPlane* CPlaneCrewFactory::getPlaneFromUser()
{
	CPlane* cPlane;
	char model[MAX];
	int planeType, seats;
	float maxWeight, maxVolume;

	do
	{
		cout << "Please enter plane type(0-Regular, 1-Cargo): ";
		cin >> planeType;

		if (planeType != 0 || planeType != 1)
			cout << "Wrong input, Please try again" << endl;
	} while (planeType != 0 || planeType != 1);

	cout << "\nPlease enter model: ";
	cin.getline(model, MAX);
	cout << "\nPlease enter number of seats: ";
	cin >> seats;

	if (planeType == eRegular)
		cPlane = new CPlane(seats, model);
	else
	{
		cout << "\nPlease enter max weight: ";
		cin >> maxWeight;
		cout << "\nPlease enter max volume: ";
		cin >> maxVolume;

		cPlane = new CCargo(seats, model, maxWeight, maxVolume);
	}

	return cPlane;
}

CCrewMember* CPlaneCrewFactory::getCrewFromUser()
{
	CCrewMember* cCrewMember;
	char name[MAX];
	int crewType, hostType, flyMinutes;
	bool isCaptain;
	CAddress *homeAddress;

	do
	{
		cout << "Please enter crew type(0-Host, 1-Pilot): ";
		cin >> crewType;

		if (crewType != 0 || crewType != 1)
			cout << "Wrong input, Please try again" << endl;
	} while (crewType != 0 || crewType != 1);

	cout << "\nPlease enter name: ";
	cin.getline(name, MAX);
	cout << "\nPlease enter fly minutes: ";
	cin >> flyMinutes;

	if (crewType == eHost)
	{
		cout << "Please enter host type(0-Regular, 1-Super, 2-Calcelan): ";
		cin >> hostType;

		cCrewMember = new CHost(name, (CHost::eType)hostType, flyMinutes);
	}
	else
	{
		cout << "\nIs Captain? (true/false) ";
		cin >> isCaptain;
		homeAddress = getAddressFromUser();

		cCrewMember = new CPilot(name, isCaptain, homeAddress, flyMinutes);
	}

	return cCrewMember;
}

CFlight* CPlaneCrewFactory::getFlightFromUser()
{
	CFlight* pFlight;
	CPlane* plane;
	CCrewMember* pCrewMember;
	char dest[MAX];
	int fNum, flightMinutes, destiny;
	bool addData;

	cout << "\nPlease enter dest: ";
	cin.getline(dest, MAX);
	cout << "\nPlease enter flight number: ";
	cin >> fNum;
	cout << "\nPlease enter flight minutes: ";
	cin >> flightMinutes;
	cout << "\nPlease enter destiny: ";
	cin >> destiny;

	CFlightInfo flightInfo(dest, fNum, flightMinutes, destiny);
	plane = getPlaneFromUser();
	pFlight = new CFlight(flightInfo, plane);

	do
	{
		cout << "Add new crew member? (true/false) ";
		cin >> addData;

		if (!addData)
			break;

		pCrewMember = getCrewFromUser();
		*pFlight + pCrewMember;
	} while (addData);

	return pFlight;
}

CCrewMember* CPlaneCrewFactory::getCrewMemberFromFile(ifstream& inFile)
{
	int crewType;
	CCrewMember* pCrewMember;
	inFile >> crewType;

	if (crewType == eHost)
		pCrewMember = new CHost(inFile);
	else
		pCrewMember = new CPilot(inFile);

	return pCrewMember;
}

CPlane* CPlaneCrewFactory::getPlaneFromFile(ifstream& inFile)
{
	int planeType;
	CPlane* pPlane;
	inFile >> planeType;

	if (planeType == eRegular)
		pPlane = new CPlane(inFile);
	else
		pPlane = new CCargo(inFile);

	return pPlane;
}
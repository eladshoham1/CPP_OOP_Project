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
	char addData, name[MAX];
	CCrewMember* pCrewMember;
	CPlane* pPlane;

	cout << "Please enter flight company name: ";
	cin.getline(name, MAX);
	comp.setName(name);

	do
	{
		cout << "Add new crew member? (Y/N) ";
		cin >> addData;

		if (addData == 'N' || addData == 'n')
			break;

		pCrewMember = getCrewFromUser();
		comp.addCrewMember(*pCrewMember);
	} while (addData == 'Y' || addData == 'y');

	do
	{
		cout << "Add new plane? (Y/N) ";
		cin >> addData;

		if (addData == 'N' || addData == 'n')
			break;

		pPlane = getPlaneFromUser();
		comp.addPlane(*pPlane);
	} while (addData == 'Y' || addData == 'y');

	do
	{
		cout << "Add new flight? (Y/N) ";
		cin >> addData;

		if (addData == 'N' || addData == 'n')
			break;

		getFlightFromUser(comp);
	} while (addData == 'Y' || addData == 'y');
}

CAddress* CPlaneCrewFactory::getAddressFromUser()
{
	CAddress* cAddress;
	int homeNumber;
	char street[MAX], city[MAX];

	cout << "Please enter home number: ";
	cin >> homeNumber;
	cleanBuffer();
	cout << "Please enter street: ";
	cin.getline(street, MAX);
	cout << "Please enter city: ";
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
		cout << "Please enter plane type (0-Regular, 1-Cargo): ";
		cin >> planeType;

		if (planeType != 0 && planeType != 1)
			cout << "Wrong input, Please try again" << endl;
	} while (planeType != 0 && planeType != 1);

	cleanBuffer();
	cout << "Please enter model: ";
	cin.getline(model, MAX);
	cout << "Please enter number of seats: ";
	cin >> seats;

	if (planeType == eRegular)
		cPlane = new CPlane(seats, model);
	else
	{
		cout << "Please enter max weight: ";
		cin >> maxWeight;
		cout << "Please enter max volume: ";
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
	char isCaptain;
	CAddress *homeAddress;

	do
	{
		cout << "Please enter crew type (0-Host, 1-Pilot): ";
		cin >> crewType;

		if (crewType != 0 && crewType != 1)
			cout << "Wrong input, Please try again" << endl;
	} while (crewType != 0 && crewType != 1);

	cleanBuffer();
	cout << "Please enter name: ";
	cin.getline(name, MAX);

	cout << "Please enter fly minutes: ";
	cin >> flyMinutes;

	if (crewType == eHost)
	{
		cout << "Please enter host type (0-Regular, 1-Super, 2-Calcelan): ";
		cin >> hostType;

		cCrewMember = new CHost(name, (CHost::eType)hostType, flyMinutes);
	}
	else
	{
		cout << "Is Captain? (Y/N) ";
		cin >> isCaptain;
		homeAddress = getAddressFromUser();

		cCrewMember = new CPilot(name, isCaptain == 'Y' || isCaptain == 'y', homeAddress, flyMinutes);
	}

	return cCrewMember;
}

void CPlaneCrewFactory::getFlightFromUser(CFlightCompany& comp)
{
	CPlane* plane = nullptr;
	CCrewMember* crewMember;
	char dest[MAX];
	int fNum, flightMinutes, destiny, index, numOfPlanes = 0, numOfCrews = 0;
	char addData;

	cleanBuffer();
	cout << "Please enter dest: ";
	cin.getline(dest, MAX);
	cout << "Please enter flight number: ";
	cin >> fNum;
	cout << "Please enter flight minutes: ";
	cin >> flightMinutes;
	cout << "Please enter destiny: ";
	cin >> destiny;

	numOfPlanes = comp.getCurrentPlanes();
	if (numOfPlanes > 0)
	{
		cout << "Please choose plane: " << endl;
		for (int i = 0; i < numOfPlanes; i++)
			cout << (i + 1) << ") " << comp[i] << endl;
		cin >> index;

		const CPlane* cPlane = dynamic_cast<const CPlane*>(&comp[index - 1]);
		const CCargo* cCargo = dynamic_cast<const CCargo*>(&comp[index - 1]);
		if (cPlane)
			plane = new CPlane(*cPlane);
		else if (cCargo)
			plane = new CPlane(*cCargo);
	}

	CFlightInfo flightInfo(dest, fNum, flightMinutes, destiny);
	CFlight flight(flightInfo, plane);

	numOfCrews = comp.getCrewCount();
	if (numOfCrews > 0)
	{
		do
		{
			cout << "Add new crew member? (Y/N) ";
			cin >> addData;

			if (!addData == 'N' || addData == 'n')
				break;

			cout << "Please choose crew member: " << endl;
			for (int i = 0; i < numOfPlanes; i++)
				cout << (i + 1) << ") " << *comp.getCrewMember(i) << endl;
			cin >> index;
			crewMember = comp.getCrewMember(index - 1);
			flight + crewMember;
			numOfCrews--;
		} while (numOfCrews > 0 && (addData == 'Y' || addData == 'y'));
	}

	comp.addFlight(flight);
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

void CPlaneCrewFactory::cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}
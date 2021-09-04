#include <fstream>
#include <iostream>
using namespace std;

#include "PlaneCrewFactory.h"

planeType CPlaneCrewFactory::getPlaneType(const CPlane* pPlane)
{
	if (typeid(*pPlane) == typeid(CPlane))
		return eRegular;
	else if (typeid(*pPlane) == typeid(CCargo))
		return eCargo;

	return nofPlaneType;
}

crewType CPlaneCrewFactory::getCrewType(const CCrewMember* pCrew)
{
	if (typeid(*pCrew) == typeid(CHost))
		return eHost;
	else if (typeid(*pCrew) == typeid(CPilot))
		return ePilot;

	return nofCrewType;
}

void CPlaneCrewFactory::getCompanyDataFromUser(CFlightCompany& comp)
{
	int option;

	do
	{
		cout << endl << "Please choose one of the following options:" << endl;
		cout << "1 - Add crew member" << endl;
		cout << "2 - Add plane" << endl;
		cout << "3 - Add flight" << endl;
		cout << "4 - Exit" << endl;
		cin >> option;

		switch (option)
		{
		case 1: 
			comp.addCrewMember(*getCrewFromUser());
			break;
		case 2:
			comp.addPlane(*getPlaneFromUser());
			break;
		case 3:
			getFlightFromUser(comp);
			break;
		case 4:
			break;
		default:
			cout << "Invalid input" << endl;
		}
	} while (option != 4);
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
		//try
		//{
			cout << "Please enter crew type (0-Host, 1-Pilot): ";
			cin >> crewType;

			if (crewType != 0 && crewType != 1)
				cout << "Wrong input, Please try again" << endl;
		/*}
		catch (...)
		{
			cout << "Invalid input, Please try again" << endl;
		}*/
	} while (crewType != 0 && crewType != 1);

	cleanBuffer();
	cout << "Please enter name: ";
	cin.getline(name, MAX);

	cout << "Please enter fly minutes: ";
	cin >> flyMinutes;

	if (crewType == eHost)
	{
		do
		{
			cout << "Please enter host type (0-Regular, 1-Super, 2-Calcelan): ";
			cin >> hostType;

			if (hostType < 0 || hostType > 2)
				cout << "Wrong input, Please try again" << endl;
		} while (hostType < 0 || hostType > 2);

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


CAddress* CPlaneCrewFactory::getAddressFromUser()
{
	int homeNumber;
	char street[MAX], city[MAX];

	cleanBuffer();
	cout << "Please enter home number: ";
	cin >> homeNumber;
	cleanBuffer();
	cout << "Please enter street: ";
	cin.getline(street, MAX);
	cout << "Please enter city: ";
	cin.getline(city, MAX);

	return new CAddress(homeNumber, street, city);
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

	CFlightInfo flightInfo(dest, fNum, flightMinutes, destiny);
	CFlight flight(flightInfo);

	numOfPlanes = comp.getCurrentPlanes();
	if (numOfPlanes > 0)
	{
		cout << "Please choose plane: " << endl;
		for (int i = 0; i < numOfPlanes; i++)
			cout << (i + 1) << ") " << comp[i];
		cin >> index;

		CPlane* cPlane = dynamic_cast<CPlane*>(&comp[index - 1]);
		CCargo* cCargo = dynamic_cast<CCargo*>(&comp[index - 1]);
		if (cPlane)
			flight.setPlane(cPlane);
		else if (cCargo)
			flight.setPlane(cCargo);
	}

	numOfCrews = comp.getCrewCount();
	if (numOfCrews > 0)
	{
		do
		{
			cout << "Add new crew member? (Y/N) ";
			cin >> addData;

			if (addData == 'N' || addData == 'n')
				break;

			cout << "Please choose crew member: " << endl;
			for (int i = 0; i < numOfPlanes; i++)
				cout << (i + 1) << ") " << *comp.getCrewMember(i);
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
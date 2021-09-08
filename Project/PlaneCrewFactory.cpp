#include <fstream>
#include <iostream>
using namespace std;

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
	int option;

	do
	{
		cout << endl << "Please choose one of the following options:" << endl;
		cout << "1 - Add crew member" << endl;
		cout << "2 - Add plane" << endl;
		cout << "3 - Exit" << endl;
		cin >> option;

		switch (option)
		{
		case 1: 
			try
			{
				comp.addCrewMember(*getCrewFromUser());
			}
			catch (CFlightCompException& e)
			{
				e.show();
			}
			break;
		case 2:
			try
			{
				comp.addPlane(*getPlaneFromUser());
			}
			catch (CFlightCompException& e)
			{
				e.show();
			}
			break;
		case 3:
			break;
		default:
			cout << "Invalid option" << endl;
		}
	} while (option != 3);
}

CPlane* CPlaneCrewFactory::getPlaneFromUser()
{
	CPlane* cPlane = nullptr;
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
	{
		try
		{
			cPlane = new CPlane(seats, model);
		}
		catch (CCompStringException& e)
		{
			CPlane::generateNumber--;
			e.show();
		}
	}
	else
	{
		cout << "Please enter max weight: ";
		cin >> maxWeight;
		cout << "Please enter max volume: ";
		cin >> maxVolume;

		try
		{
			cPlane = new CCargo(seats, model, maxWeight, maxVolume);
		}
		catch (CCompStringException& e)
		{
			CPlane::generateNumber--;
			e.show();
		}
	}

	return cPlane;
}

CCrewMember* CPlaneCrewFactory::getCrewFromUser()
{
	CCrewMember* cCrewMember = nullptr;
	CAddress *homeAddress = nullptr;
	char name[MAX];
	int crewType, hostType, flyMinutes;
	char isCaptain;

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

	if ((CrewType)crewType == eHost)
	{
		do
		{
			cout << "Please enter host type (0-Regular, 1-Super, 2-Calcelan): ";
			cin >> hostType;

			if (hostType < 0 || hostType > 2)
				cout << "Wrong input, Please try again" << endl;
		} while (hostType < 0 || hostType > 2);

		try
		{
			cCrewMember = new CHost(name, (CHost::eType)hostType, flyMinutes);
		}
		catch (CCompStringException& e)
		{
			e.show();
		}
	}
	else
	{
		cout << "His Captain? (Y,y - yes/Any other key - no) ";
		cin >> isCaptain;

		try
		{
			homeAddress = getAddressFromUser();
		}
		catch (CCompStringException& e)
		{
			e.show();
		}

		try
		{
			cCrewMember = new CPilot(name, isCaptain == 'Y' || isCaptain == 'y', homeAddress, flyMinutes);
		}
		catch (CCompStringException& e)
		{
			e.show();
		}
	}

	return cCrewMember;
}

CAddress* CPlaneCrewFactory::getAddressFromUser() throw(CCompStringException)
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

CCrewMember* CPlaneCrewFactory::getCrewMemberFromFile(ifstream& inFile)
{
	CCrewMember* pCrewMember;
	int crewType;
	inFile >> crewType;

	if ((CrewType)crewType == eHost)
		pCrewMember = new CHost(inFile);
	else
		pCrewMember = new CPilot(inFile);

	return pCrewMember;
}

CPlane* CPlaneCrewFactory::getPlaneFromFile(ifstream& inFile)
{ 
	CPlane* pPlane;
	int planeType;
	inFile >> planeType;

	if ((PlaneType)planeType == eRegular)
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
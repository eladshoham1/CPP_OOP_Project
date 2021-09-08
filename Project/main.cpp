#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

#include "Plane.h"
#include "FlightInfo.h"
#include "CrewMember.h"
#include "Flight.h"
#include "FlightCompany.h"
#include "Address.h"
#include "Pilot.h"
#include "Cargo.h"
#include "Host.h"
#include "FlightCompException.h"
#include "PlaneCrewFactory.h"

int main()
{
	CFlightCompany* pDelta = nullptr;
	try
	{
		pDelta = new CFlightCompany("Delta.txt", 0);
		cout << "This was in file " << endl;
		pDelta->print(cout);
	}
	catch (const CFlightCompException& e) 
	{
		e.show();
		pDelta = new CFlightCompany("Delta");
	}
	cout << endl;
	try
	{
		CPlane p1(-34, "AirBus");
	}
	catch (const CCompStringException& e)
	{
		CPlane::generateNumber--;
		e.show();
	}
	
	try
	{
		CCargo c1(45, "Jumbo", -560, 200);
	}
	catch (const CCompStringException& e)
	{
		CPlane::generateNumber--;
		e.show();
	}

	try
	{
		CCargo c2(45, "Jumbo", 560, -200);
	}
	catch (const CCompStringException& e)
	{
		CPlane::generateNumber--;
		e.show();
	}

	try
	{
		CFlightInfo f1("London", -23, 120, 5000);
	}
	catch (const CCompStringException& e)
	{
		e.show();
	}

	try
	{
		CFlightInfo f2("LondonVeryLong", 23, 120, 5000);
	}
	catch (const CCompStringException& e)
	{
		e.show();
	}

	try
	{
		CFlightInfo f3("London", 23, -120, 5000);
	}
	catch (const CCompStringException& e)
	{
		e.show();
	}

	try
	{
		CFlightInfo f4("London", 23, 120, -5000);
	}
	catch (const CCompStringException& e)
	{
		e.show();
	}

	try
	{
		CCrewMember* pC1 = pDelta->getCrewMember(-1);
	}
	catch (const CFlightCompException& e)
	{
		e.show();
	}

	try
	{
		CCrewMember* pC2 = pDelta->getCrewMember(0);
		(*pC2) += -4;
	}
	catch (const CFlightCompException& e)
	{
		e.show();
	}

	try
	{
		CPlane p0 = (*pDelta)[9];
	}
	catch (const CFlightCompException& e)
	{
		e.show();
	}

	CPlaneCrewFactory::getCompanyDataFromUser(*pDelta);

	cout << endl;

	try
	{
		CFlightInfo Info("Paris", 343, 320, 5000);
		CFlight flight1(Info, &(*pDelta)[0]);
		pDelta->addFlight(flight1);
	}
	catch (CFlightCompException& e)
	{
		e.show();
	}

	try
	{
		CFlight* pF = pDelta->getFlightByNum(343);
		CCrewMember* pCmTemp;
		if (pF != nullptr)
		{
			cout << "flight 343 was found " << endl;
			for (int i = 0; i < pDelta->getCrewCount(); i++)
			{
				pCmTemp = pDelta->getCrewMember(i);
				*pF + pCmTemp;
			}
		}
	}
	catch (CFlightCompException& e)
	{
		e.show();
	}

	try
	{
		pDelta->saveToFile("Delta.txt");
	}
	catch (const CFlightCompException& e) 
	{
		e.show();
	}

	delete pDelta;
	system("pause");
	return 0;
}
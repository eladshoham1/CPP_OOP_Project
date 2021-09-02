#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

#include "Plane.h"
#include "FlightInfo.h"
#include "CrewMember.h"
#include "Flight.h"
#include "FlightCompany.h"
#include "address.h"
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
	catch (const CFlightCompException& e) {
		e.show();
		pDelta = new CFlightCompany("Delta");
	}
	//Checking some of the exception put try and catch for each section	

	/*CPlane p1(-34, "AirBus");
	CCargo c1(45, "Jumbo", -560, 200);
	CCargo c2(45, "Jumbo", 560, -200);
	CFlightInfo f1("London", -23, 120, 5000);
	CFlightInfo f2("LondonVeryLong", 23, 120, 5000);
	CFlightInfo f3("London", 23, -120, 5000);
	CFlightInfo f4("London", 23, 120, -5000);
	CCrewMember* pC1 = pDelta->getCrewMember(-1);

	CCrewMember* pC2 = pDelta->getCrewMember(0);
	(*pC2) += -4;
	CPlane p0 = (*pDelta)[9];*/

	//call a static function that get plane or customer from user.
	/*CPlaneCrewFactory::getCompanyDataFromUser(*pDelta);

	CFlightInfo Info("Paris", 343, 320, 5000);
	CFlight flight1(Info, &(*pDelta)[0]);
	pDelta->addFlight(flight1);

	CFlight* pF = pDelta->getFlightByNum(343);
	CCrewMember* pCmTemp;
	if (pF != nullptr) {
		cout << "flight 343 was found " << endl;
		for (int i = 0; i < pDelta->getCrewCount(); i++) {
			pCmTemp = pDelta->getCrewMember(i);
			*pF + pCmTemp;
		}
	}*/

	try
	{
		pDelta->saveToFile("Delta.txt");
	}
	catch (const CFlightCompException& e) {
		e.show();
	}

	delete pDelta;
	system("pause");
	return 0;
}
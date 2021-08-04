#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

#include "Plane.h"
#include "FlightInfo.h"
#include "CrewMember.h"
#include "Flight.h"
#include "Address.h"
#include "Address.h"
#include "FlightCompany.h"


int main()
{
	cout << endl << "Checking Address" << endl;
	CAddress a(0, NULL,NULL);
	cin >> a;
	cout << a;

	cout << endl << "Checking CFlightCompany" << endl;

	CFlightCompany* pDelta = new CFlightCompany("Delta");
	cout << endl << "First company" << endl;
	pDelta->print(cout);


	CCrewMember* pCmArr[3];

	pCmArr[0] = new CCrewMember("Momo", 125);
	pCmArr[1] = new CCrewMember("Gogo");
	pCmArr[2] = new CCrewMember("Jojo", 60);

	if (!((*pCmArr[1]) += 200))
		cout << "error update minutes" << endl;

	for (int i = 0; i < 3; i++)
		if (!pDelta->addCrewMember(*pCmArr[i]))
			cout << "Problem adding crew member " << i + 1 << endl;

	cout << "******** try adding CrewMembers again *********" << endl;
	//Create another array that is equal to the first array
	CCrewMember* crewsDup[3];
	for (int i = 0; i < 3; i++)
		crewsDup[i] = new CCrewMember(*pCmArr[i]);

	for (int i = 0; i < 3; i++) {
		if (!pDelta->addCrewMember(*pCmArr[i]))
			cout << "Problem adding crew member " << i + 1 << endl;
	}

	for (int i = 0; i < 3; i++)
		delete crewsDup[i];

	for (int i = 0; i < 3; i++)
		delete pCmArr[i];

	cout << "******** After adding Crew member *********" << endl;
	pDelta->print(cout);


	CPlane* pPlaneArr[2];
	pPlaneArr[0] = new CPlane(100, "Boing373");  //seats,degem
	pPlaneArr[1] = new CPlane(10, "Boing3");

	cout << "Before adding seats" << endl;
	cout << *pPlaneArr[1];

	//Adding seats
	(*pPlaneArr[1])++;
	++(*pPlaneArr[1]);

	cout << "After adding seats" << endl;
	cout << *pPlaneArr[1];

	for (int i = 0; i < 2; i++)
		if (!pDelta->addPlane(*pPlaneArr[i]))
			cout << "Problem adding plane " << i + 1 << endl;

	for (int i = 0; i < 2; i++)
		delete pPlaneArr[i];

	cout << "******** After adding Planes *********" << endl;
	pDelta->print(cout);

	CFlightInfo fInfo1("Paris", 343, 320, 5000);
	CFlightInfo fInfo2("Rome", 506, 220, 4000);

	cout << fInfo1;
	cout << fInfo2;

	if (fInfo1 != fInfo2)
		cout << "FlightInfo not equal" << endl;
	else
		cout << "FlightInfo equal" << endl;

	cout << "Flight time is: " << (int)fInfo1;

	Flight* fArr[2];
	fArr[0] = new Flight(fInfo1);
	fArr[1] = new Flight(fInfo2, pDelta->getPlane(1));

	cout << "Before seting plane" << endl;
	cout << *fArr[0];
	fArr[0]->setPlane(pDelta->getPlane(0));

	cout << "After seting plane " << endl;
	cout << *fArr[0];

	for (int i = 0; i < 2; i++)
		if (!pDelta->addFlight(*fArr[i]))
			cout << "Problem adding flight " << i + 1 << endl;

	for (int i = 0; i < 2; i++)
		delete fArr[i];

	cout << "******** After adding Flights *********" << endl;
	pDelta->print(cout);

	pDelta->addCrewToFlight(fInfo1.getFNum(), CCrewMember::START_ID);
	pDelta->addCrewToFlight(fInfo1.getFNum(), CCrewMember::START_ID + 1);
	pDelta->addCrewToFlight(fInfo1.getFNum(), CCrewMember::START_ID + 2);

	cout << "******** After adding Crew to Flight *********" << endl;
	pDelta->print(cout);

	delete pDelta;

	system("pause");
	return 0;
}
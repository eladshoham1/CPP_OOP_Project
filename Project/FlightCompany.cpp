#include <iostream>
#include <string.h>
using namespace std;

#include "FlightCompany.h"

CFlightCompany::CFlightCompany(const char* name)
{
	setName(name);
}

CFlightCompany::CFlightCompany(const CFlightCompany& cFlightCompany)
{
	setName(cFlightCompany.name);
}

CFlightCompany::~CFlightCompany()
{
	delete[] this->name;
}

char* CFlightCompany::getName()
{
	return this->name;
}

void CFlightCompany::setName(const char* name)
{
	this->name = _strdup(name);
}

void CFlightCompany::print(ostream& out) const
{
	out << "Flight company: " << this->name << endl;
}
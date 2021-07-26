#include <iostream>
#include <string.h>
using namespace std;

#include "CrewMember.h"

CCrewMember::CCrewMember(const char* name, int flyMinutes)
{
	setName(name);
	this->flyMinutes = flyMinutes;
}

CCrewMember::CCrewMember(const CCrewMember& cCrewMember)
{
	setName(cCrewMember.name);
	this->flyMinutes = cCrewMember.flyMinutes;
}

CCrewMember::~CCrewMember()
{
	delete[] this->name;
}

bool CCrewMember::updateMinutes(int minutes)
{
	if (this->flyMinutes + minutes < 0)
		return false;

	this->flyMinutes += minutes;
	return true;
}

char* CCrewMember::getName()
{
	return this->name;
}

void CCrewMember::setName(const char* name)
{
	this->name = _strdup(name);
}

int CCrewMember::getFlyMinutes()
{
	return this->flyMinutes;
}

void CCrewMember::print(ostream& out) const
{
	out << "Crewmember " << this->name << " minutes " << this->flyMinutes << endl;
}

bool CCrewMember::isEqual(const CCrewMember& cCrewMember)
{
	return strcmp(this->name, cCrewMember.name) == 0;
}
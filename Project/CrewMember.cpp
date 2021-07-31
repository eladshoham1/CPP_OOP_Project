#include <iostream>
#include <string.h>
using namespace std;

#include "CrewMember.h"

int CCrewMember::generateNumber = 1000;

CCrewMember::CCrewMember(const char* name, int flyMinutes)
{
	this->workerId = CCrewMember::generateNumber++;
	setName(name);
	this->flyMinutes = flyMinutes;
}

CCrewMember::CCrewMember(const CCrewMember& cCrewMember)
{
	this->workerId = cCrewMember.workerId;
	setName(cCrewMember.name);
	this->flyMinutes = cCrewMember.flyMinutes;
}

CCrewMember::~CCrewMember()
{
	delete[] this->name;
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

const CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
	if (this != &other)
	{
		delete[] this->name;
		this->name = _strdup(other.name);
		this->flyMinutes = other.flyMinutes;
	}

	return *this;
}

const CCrewMember& CCrewMember::operator+=(int minutes)
{
	if (this->flyMinutes + minutes < 0)
		this->flyMinutes = 0;
	else
		this->flyMinutes += minutes;

	return *this;
}

bool CCrewMember::operator==(const CCrewMember& other) const
{
	return this->workerId == other.workerId;
}
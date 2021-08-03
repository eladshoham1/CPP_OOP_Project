#include <iostream>
#include <string.h>
using namespace std;

#include "CrewMember.h"

int CCrewMember::generateID = START_ID;

CCrewMember::CCrewMember(const char* name, int flyMinutes)
{
	this->workerId = CCrewMember::generateID++;
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

int CCrewMember::getWorkerId() const
{
	return this->workerId;
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

bool CCrewMember::operator+=(int minutes)
{
	if (this->flyMinutes + minutes < 0)
		return false;

	this->flyMinutes += minutes;
	return true;
}

bool CCrewMember::operator==(const CCrewMember& other) const
{
	return this->workerId == other.workerId;
}
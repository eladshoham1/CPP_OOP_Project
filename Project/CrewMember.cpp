#include <iostream>
using namespace std;
#include <string.h>

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
	*this = cCrewMember;
}

CCrewMember::~CCrewMember()
{
	delete[] this->name;
}

int CCrewMember::getWorkerId() const
{
	return this->workerId;
}

const char* CCrewMember::getName() const
{
	return this->name;
}

int CCrewMember::getFlyMinutes() const
{
	return this->flyMinutes;
}

void CCrewMember::setWorkerId(int workerId)
{
	this->workerId = workerId;
}

void CCrewMember::setName(const char* name)
{
	delete[] this->name;
	this->name = _strdup(name);
}

void CCrewMember::setFlyMinutes(int flyMinutes)
{
	this->flyMinutes = flyMinutes;
}

void CCrewMember::print(ostream& out) const
{
	out << *this;
}

bool CCrewMember::isEqual(const CCrewMember& cCrewMember) const
{
	return strcmp(this->name, cCrewMember.name) == 0;
}

const CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
	if (this != &other)
	{
		setWorkerId(other.workerId);
		setName(other.name);
		setFlyMinutes(other.flyMinutes);
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

ostream& operator<<(ostream& os, const CCrewMember& cCrewMember)
{
	os << "Crewmember " << cCrewMember.name << " minutes " << cCrewMember.flyMinutes << endl;
	return os;
}
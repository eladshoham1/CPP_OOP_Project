#include <iostream>
using namespace std;
#include <string.h>

#include "CrewMember.h"

CCrewMember::CCrewMember(const char* name, int flyMinutes)
{
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

const char* CCrewMember::getName() const
{
	return this->name;
}

int CCrewMember::getFlyMinutes() const
{
	return this->flyMinutes;
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

void CCrewMember::getPresent() const
{
	cout << this->name << " thanking the company for receiving the holiday gift." << endl;
}

const CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
	if (this != &other)
	{
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
	return strcmp(this->name, other.name) == 0;
}

ostream& operator<<(ostream& os, const CCrewMember& cCrewMember)
{
	os << "Crewmember " << cCrewMember.name << " minutes " << cCrewMember.flyMinutes << endl;
	return os;
}
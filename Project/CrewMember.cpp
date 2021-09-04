#include <fstream>
using namespace std;
#include <string.h>

#include "CrewMember.h"

CCrewMember::CCrewMember(const char* name, int flyMinutes) throw(CCompStringException)
{
	setName(name);
	setFlyMinutes(flyMinutes);
}

CCrewMember::CCrewMember(ifstream& in)
{
	in >> *this;
}

CCrewMember::CCrewMember(const CCrewMember& cCrewMember) throw(CCompStringException)
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

void CCrewMember::setName(const char* name) throw(CCompStringException)
{
	if (strcmp(name, "") == 0)
		throw CCompStringException("Name can't be empty");

	delete[] this->name;
	this->name = _strdup(name);
}

void CCrewMember::setFlyMinutes(int flyMinutes) throw(CCompStringException)
{
	if (flyMinutes < 0)
		throw CCompStringException("Fly minutes have to be positive number");

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
	cout << this->name << " thanking the company for receiving the holiday gift" << endl;
}

void CCrewMember::takeOff(int minutes) throw(CCompStringException)
{
	if (minutes < 0)
		throw CCompStringException("Minutes have to be positive number");

	this->flyMinutes += minutes;
}

const CCrewMember& CCrewMember::operator=(const CCrewMember& other) throw(CCompStringException)
{
	if (this != &other)
	{
		setName(other.name);
		setFlyMinutes(other.flyMinutes);
	}

	return *this;
}

void CCrewMember::operator+=(int minutes) throw(CCompStringException)
{
	if (minutes < 0)
		throw CCompStringException("Minutes have to be positive number");

	this->flyMinutes += minutes;
}

bool CCrewMember::operator==(const CCrewMember& other) const
{
	return strcmp(this->name, other.name) == 0;
}

ostream& operator<<(ostream& os, const CCrewMember& cCrewMember)
{
	if (typeid(os) == typeid(ofstream))
		os << cCrewMember.name << " " << cCrewMember.flyMinutes;
	else
		os << typeid(cCrewMember).name() + 7 << ": " << cCrewMember.name << " minutes " << cCrewMember.flyMinutes;

	cCrewMember.toOs(os);
	return os;
}

istream& operator>>(istream& in, CCrewMember& cCrewMember)
{
	delete[] cCrewMember.name;
	cCrewMember.name = new char[MAX_SIZE];

	if (typeid(in) == typeid(ifstream))
		in >> cCrewMember.name >> cCrewMember.flyMinutes;
	else
	{
		/*int crewType;

		do
		{
			cout << "Please enter crew type (0-Host, 1-Pilot): ";
			in >> crewType;

			if (crewType != 0 || crewType != 1)
				cout << "Wrong input, Please try again" << endl;
		} while (crewType != 0 || crewType != 1);

		cout << "Please enter name: ";
		in.getline(cCrewMember.name, MAX_SIZE);
		cout << "Please enter fly minutes: ";
		in >> cCrewMember.flyMinutes;*/
	}

	cCrewMember.fromOs(in);
	return in;
}
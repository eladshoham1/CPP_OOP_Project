#include <iostream>
using namespace std;

#include "Pilot.h"

CPilot::CPilot(const char *name, bool isCaptain, CAddress *homeAddress, int flyMinutes) : CCrewMember(name, flyMinutes)
{
	setIsCaptain(isCaptain);
	setHomeAddress(homeAddress);
}

CPilot::CPilot(const CPilot& cPilot) : CCrewMember(cPilot)
{
	setIsCaptain(cPilot.isCaptain);
	setHomeAddress(cPilot.homeAddress);
}

CPilot::~CPilot()
{
	if (this->homeAddress != nullptr)
		delete this->homeAddress;
}

void CPilot::setIsCaptain(bool isCaptain)
{
	this->isCaptain = isCaptain;
}

void CPilot::setHomeAddress(CAddress *homeAddress)
{
	delete this->homeAddress;
	if (homeAddress != nullptr)
		this->homeAddress = new CAddress(*homeAddress);
}

void CPilot::toSimulator() const
{
	cout << "Pilot " << this->name << " got the message will come soon" << endl;
}

void CPilot::getUniform() const
{
	cout << this->name << ": this is the fifth time I get a new uniform, this is a waste of money!" << endl;
}

void CPilot::print(ostream& out) const
{
	out << *this;
}

void CPilot::toOs(ostream& os) const
{
	os << this->name << " minutes " << this->flyMinutes;
	
	if (this->homeAddress)
		os << " Home " << *this->homeAddress;

	os << (this->isCaptain ? " a Captain" : "Not a Captain") << endl;
}

bool CPilot::operator+=(int minutes)
{
	return CCrewMember::operator+=(this->isCaptain ? int(minutes * 1.1f) : minutes);
}
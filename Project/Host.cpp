#include <fstream>
using namespace std;

#include "Host.h"

CHost::CHost(const char* name, eType hostType, int flyMinutes) : CCrewMember(name, flyMinutes)
{
	setHostType(hostType);
}

CHost::CHost(ifstream& in) : CCrewMember(in)
{
	fromOs(in);
}

CHost::CHost(const CHost& cHost) : CCrewMember(cHost)
{
	setHostType(cHost.hostType);
}

CHost::eType CHost::getHostType() const
{
	return this->hostType;
}

void CHost::setHostType(eType hostType)
{
	this->hostType = hostType;
}

void CHost::getPresent() const
{
	CCrewMember::getPresent();
	cout << "I was not expecting it" << endl;
}

void CHost::getUniform() const
{
	cout << this->name << ": I think the new uniform is very nice!" << endl;
}

void CHost::toOs(ostream& os) const
{
	os << types[this->hostType] << " " << this->name << " minutes " << this->flyMinutes << endl;
}

void CHost::fromOs(istream& in)
{
	int hostType;

	if (typeid(in) != typeid(ifstream))
		cout << "Please enter host type(0-Regular, 1-Super, 2-Calcelan): ";

	in >> hostType;
	this->hostType = (eType)hostType;
}
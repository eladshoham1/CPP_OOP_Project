#include <iostream>
using namespace std;

#include "Host.h"

CHost::CHost(const char* name, type hostType, int flyMinutes) : CCrewMember(name, flyMinutes)
{
	this->hostType = hostType;
}

CHost::CHost(const CHost& cHost) : CCrewMember(cHost)
{
	setHostType(cHost.hostType);
}

void CHost::setHostType(type hostType)
{
	this->hostType = hostType;
}

void CHost::getPresent() const
{
	CCrewMember::getPresent();
	cout << "I wasn’t expecting it" << endl;
}

void CHost::getUniform() const
{
	cout << "I think the new uniform is very nice!" << endl;
}
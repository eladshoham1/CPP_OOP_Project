#include <fstream>
using namespace std;

#include "Pilot.h"

CPilot::CPilot(const char *name, bool isCaptain, CAddress *homeAddress, int flyMinutes) : CCrewMember(name, flyMinutes)
{
	setIsCaptain(isCaptain);
	setHomeAddress(homeAddress);
}

CPilot::CPilot(ifstream& in) : CCrewMember(in)
{
	fromOs(in);
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
	if (homeAddress == nullptr)
		throw CCompStringException("Home address can't be null");

	delete this->homeAddress;
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
	if (typeid(os) == typeid(ofstream))
	{
		os << " ";

		if (this->homeAddress)
			os << 1 << " " << *this->homeAddress;
		else
			os << 0;

		os << " " << (this->isCaptain ? 1 : 0) << endl;
	}
	else
	{
		if (this->homeAddress)
			os << *this->homeAddress;

		os << (this->isCaptain ? " a Captain" : "Not a Captain") << endl;
	}
}

void CPilot::fromOs(istream& in)
{
	int hasAddress, isCaptain;

	if (typeid(in) == typeid(ifstream))
	{
		in >> hasAddress;
		if (hasAddress == 1)
			this->homeAddress = new CAddress(*dynamic_cast<ifstream*>(&in));
	}
	else
	{
		cout << "\nHas address? (0-No, 1-Yes) ";
		in >> hasAddress;

		if (hasAddress)
			in >> *this->homeAddress;

		cout << "\nIs Captain? (0-No, 1-Yes) ";
	}

	in >> isCaptain;
	this->isCaptain = isCaptain == 1;
}
	

void CPilot::operator+=(int minutes)
{
	CCrewMember::operator+=(this->isCaptain ? int(minutes * 1.1f) : minutes);
}
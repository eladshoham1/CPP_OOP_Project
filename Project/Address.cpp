#include <fstream>
using namespace std;
#include <string.h>

#include "Address.h"
#include "FlightInfo.h"

CAddress::CAddress(int homeNumber, const char* street, const char* city) throw (CCompStringException)
{
	updateAddress(city, street, homeNumber);
}

CAddress::CAddress(ifstream& in)
{
	in >> *this;
}

CAddress::CAddress(const CAddress& cAddress) throw (CCompStringException)
{
	*this = cAddress;
}

CAddress::~CAddress()
{
	delete[] this->street;
	delete[] this->city;
}

char* CAddress::getCity() const
{
	return this->city;
}

char* CAddress::getStreet() const
{
	return this->street;
}

int CAddress::getHomeNumber() const
{
	return this->homeNumber;
}

void CAddress::setCity(const char* city) throw (CCompStringException)
{
	if (strcmp(city, "") == 0)
		throw CCompStringException("City can't be empty");

	delete[] this->city;
	this->city = _strdup(city);
}

void CAddress::setStreet(const char* street) throw (CCompStringException)
{
	if (strcmp(street, "") == 0)
		throw CCompStringException("Street can't be empty");

	delete[] this->street;
	this->street = _strdup(street);
}

void CAddress::setHomeNumber(int homeNumber) throw (CCompStringException)
{
	if (homeNumber <= 0)
		throw CCompStringException("Home number need to be postivie number");

	this->homeNumber = homeNumber;
}

void CAddress::updateAddress(const char* city, const char* street, int homeNumber) throw (CCompStringException)
{
	setCity(city);
	setStreet(street);
	setHomeNumber(homeNumber);
}

const CAddress& CAddress::operator=(const CAddress& other) throw (CCompStringException)
{
	if (this != &other)
		updateAddress(other.city, other.street, other.homeNumber);

	return *this;
}

ostream& operator<<(ostream& os, const CAddress& cAddress)
{
	if (typeid(os) == typeid(ofstream))
		os << cAddress.homeNumber << " " << cAddress.street << " " << cAddress.city;
	else
		os << " Home Address: " << cAddress.street << " " << cAddress.homeNumber << ", " << cAddress.city << endl;

	return os;
}

istream& operator>>(istream& in, CAddress& cAddress)
{
	delete[] cAddress.street;
	delete[] cAddress.city;
	cAddress.street = new char[MAX];
	cAddress.city = new char[MAX];

	//if (typeid(in) != typeid(ifstream))
		//cout << "Please enter house number street name and city name:" << endl;

	in >> cAddress.homeNumber >> cAddress.street >> cAddress.city;
	return in;
}

bool CAddress::operator==(const CAddress& other) const
{
	return this->homeNumber == other.homeNumber &&
		strcmp(this->street, other.street) == 0 &&
		strcmp(this->city, other.city) == 0;
}

bool CAddress::operator!=(const CAddress& other) const
{
	return !(*this == other);
}

const CAddress& CAddress::getCurrentAddress() const
{
	return *this;
}
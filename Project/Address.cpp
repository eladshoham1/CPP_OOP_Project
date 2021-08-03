#include <iostream>
#include <string.h>
using namespace std;

#include "Address.h"

CAddress::CAddress(int homeNumber, const char* street, const char* city)
{
	updateAddress(city, street, homeNumber);
}

CAddress::~CAddress()
{
	delete[] this->street;
	delete[] this->city;
}

char* CAddress::getCity()
{
	return this->city;
}

char* CAddress::getStreet()
{
	return this->street;
}

int CAddress::getHomeNumber()
{
	return this->homeNumber;
}

void CAddress::updateAddress(const char* city, const char* street, int homeNumber)
{
	if (street == NULL)
		street = "";
	if (city == NULL)
		city = "";
	this->city = _strdup(city);
	this->street = _strdup(street);
	this->homeNumber = homeNumber;
}

const CAddress& CAddress::operator=(const CAddress& other)
{
	if (this != &other)
	{
		this->homeNumber = other.homeNumber;
		delete[] this->street;
		this->street = _strdup(other.street);
		delete[] this->city;
		this->city = _strdup(other.city);
	}

	return *this;
}

ostream& operator<<(ostream& os, const CAddress& cAddress)
{
	os << cAddress.street << " " << cAddress.homeNumber << " " << cAddress.city << endl;
	return os;
}

istream& operator>>(istream& in, CAddress& cAddress)
{
	cout << "Please enter house number street name and city name:" << endl;
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

const CAddress& CAddress::getCurrentAddress()
{
	return *this;
}
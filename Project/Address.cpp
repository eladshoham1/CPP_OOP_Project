#include <iostream>
#include <string.h>
using namespace std;

#include "Address.h"

CAddress::CAddress(int homeNumber, const char* street, const char* city)
{
	this->homeNumber = homeNumber;
	this->street = _strdup(street);
	this->city = _strdup(city);
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

void CAddress::print(ostream& out) const
{
	out << this->street << " " << this->homeNumber << ", " << this->city << endl;
}

void CAddress::updateAddress(const char* city, const char* street, int homeNumber)
{
	this->city = _strdup(city);
	this->street = _strdup(street);
	this->homeNumber = homeNumber;
}
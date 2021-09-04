#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
using namespace std;
#include <string.h>

#include "FlightInfo.h"

CFlightInfo::CFlightInfo(const char dest[], int fNum, int flightMinutes, int destiny) throw(CCompStringException)
{
	setDest(dest);
	setFNum(fNum);
	setFlightMinutes(flightMinutes);
	setDestiny(destiny);
}

CFlightInfo::CFlightInfo(ifstream& in)
{
	in >> *this;
}

CFlightInfo::CFlightInfo(const CFlightInfo& cFlightInfo) throw(CCompStringException)
{
	*this = cFlightInfo;
}

int CFlightInfo::getFNum() const
{
	return this->fNum;
}

const char* CFlightInfo::getDest() const
{
	return this->dest;
}

int CFlightInfo::getFlightMinutes() const
{
	return this->flightMinutes;
}

int CFlightInfo::getDestiny() const
{
	return this->destiny;
}

void CFlightInfo::setFNum(int fNum) throw(CCompStringException)
{
	if (fNum < 0)
		throw CCompStringException("Flight number must be positive number");

	this->fNum = fNum;
}

void CFlightInfo::setDest(const char* dest) throw(CCompStringException)
{
	if (strlen(dest) > MAX)
		throw CCompStringException("Dest name is too long");

	strcpy(this->dest, dest);
}

void CFlightInfo::setFlightMinutes(int flightMinutes) throw(CCompStringException)
{
	if (flightMinutes < 0)
		throw CCompStringException("Flight minutes must be positive number");

	this->flightMinutes = flightMinutes;
}

void CFlightInfo::setDestiny(int destiny) throw(CCompStringException)
{
	if (destiny < 0)
		throw CCompStringException("Destiny must be positive number");

	this->destiny = destiny;
}

bool CFlightInfo::isEqual(const CFlightInfo& cFlightInfo)
{
	return *this == cFlightInfo;
}

void CFlightInfo::print(ostream& out) const
{
	out << this;
}

const CFlightInfo& CFlightInfo::operator=(const CFlightInfo& other) throw(CCompStringException)
{
	if (this != &other)
	{
		setFNum(other.fNum);
		setDest(other.dest);
		setFlightMinutes(other.flightMinutes);
		setDestiny(other.destiny);
	}

	return *this;
}

ostream& operator<<(ostream& os, const CFlightInfo& cFlightInfo)
{
	if (typeid(os) == typeid(ofstream))
		os << cFlightInfo.dest << " " << cFlightInfo.fNum << " " << cFlightInfo.flightMinutes << " " << cFlightInfo.destiny;
	else
		os << "Flight Info dest: " << cFlightInfo.dest << " Number " << cFlightInfo.fNum <<
		" minutes " << cFlightInfo.flightMinutes << " KM " << cFlightInfo.destiny << endl;
	return os;
}

istream& operator>>(istream& in, CFlightInfo& cFlightInfo)
{
	if (typeid(in) == typeid(ifstream))
		in >> cFlightInfo.dest >> cFlightInfo.fNum >> cFlightInfo.flightMinutes >> cFlightInfo.destiny;
	else
	{
		cout << "Please enter dest: ";
		in.getline(cFlightInfo.dest, MAX);
		cout << "Please enter flight number: ";
		in >> cFlightInfo.fNum;
		cout << "Please enter flight minutes: ";
		in >> cFlightInfo.flightMinutes;
		cout << "Please enter destiny: ";
		in >> cFlightInfo.destiny;
	}

	return in;
}

bool CFlightInfo::operator==(const CFlightInfo& other) const
{
	return this->fNum == other.fNum;
}

bool CFlightInfo::operator!=(const CFlightInfo& other) const
{
	return !(*this == other);
}
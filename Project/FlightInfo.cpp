#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <string.h>

#include "FlightInfo.h"

CFlightInfo::CFlightInfo(const char dest[], int fNum, int flightMinutes, int destiny)
{
	setDest(dest);
	this->fNum = fNum;
	this->flightMinutes = flightMinutes;
	this->destiny = destiny;
}

CFlightInfo::CFlightInfo(const CFlightInfo& cFlightInfo)
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

void CFlightInfo::setFNum(int fNum) 
{
	this->fNum = fNum;
}

void CFlightInfo::setDest(const char* dest)
{
	strcpy(this->dest, dest);
}

void CFlightInfo::setFlightMinutes(int flightMinutes)
{
	this->flightMinutes = flightMinutes;
}

void CFlightInfo::setDestiny(int destiny)
{
	this->destiny = destiny;
}

bool CFlightInfo::isEqual(const CFlightInfo& cFlightInfo)
{
	return this->fNum == cFlightInfo.fNum;
}

void CFlightInfo::print(ostream& out) const
{
	out << this;
}

const CFlightInfo& CFlightInfo::operator=(const CFlightInfo& other)
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
	os << "Flight Info dest: " << cFlightInfo.dest << " Number " << cFlightInfo.fNum <<
		" minutes " << cFlightInfo.flightMinutes << " KM " << cFlightInfo.destiny << endl;
	return os;
}

bool CFlightInfo::operator!=(const CFlightInfo& other) const
{
	return this->fNum != other.fNum ||
		strcmp(this->dest, other.dest) != 0 ||
		this->flightMinutes != other.flightMinutes ||
		this->destiny != other.destiny;
}
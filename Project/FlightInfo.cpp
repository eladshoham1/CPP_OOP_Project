#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string.h>
using namespace std; 

#include "FlightInfo.h"

CFlightInfo::CFlightInfo(const char dest[], int fNum, int flightMinutes, int destiny)
{
	setDest(dest);
	this->fNum = fNum;
	this->flightMinutes = flightMinutes;
	this->destiny = destiny;
}

int CFlightInfo::getFNum() const
{
	return this->fNum;
}

void CFlightInfo::setFNum(int fNum)
{
	this->fNum = fNum;
}

char* CFlightInfo::getDest()
{
	return this->dest;
}

void CFlightInfo::setDest(const char dest[])
{
	strcpy(this->dest, dest);
}

int CFlightInfo::getFlightMinutes()
{
	return this->flightMinutes;
}

void CFlightInfo::setFlightMinutes(int flightMinutes)
{
	this->flightMinutes = flightMinutes;
}

int CFlightInfo::getDestiny()
{
	return this->destiny;
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
	out << "Flight Info dest: " << this->dest << " Number " << this->fNum <<
		" minutes " << this->flightMinutes << " KM " << this->destiny << endl;
}


const CFlightInfo& CFlightInfo::operator=(const CFlightInfo& other)
{
	if (this != &other)
	{
		this->fNum = other.fNum;
		strcpy(this->dest, other.dest);
		this->flightMinutes = other.flightMinutes;
		this->destiny = other.destiny;
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
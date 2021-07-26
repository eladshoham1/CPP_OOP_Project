#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string.h>
using namespace std; 

#include "FlightInfo.h"

CFlightInfo::CFlightInfo(const char dest[], int flightNum, int flightMinutes, int destiny)
{
	setDest(dest);
	this->flightNum = flightNum;
	this->flightMinutes = flightMinutes;
	this->destiny = destiny;
}

int CFlightInfo::getFlightNum()
{
	return this->flightNum;
}

char* CFlightInfo::getDest()
{
	return this->dest;
}

int CFlightInfo::getFlightMinutes()
{
	return this->flightMinutes;
}

int CFlightInfo::getDestiny()
{
	return this->destiny;
}

void CFlightInfo::setFlightNum(int flightNum)
{
	this->flightNum = flightNum;
}

void CFlightInfo::setDest(const char dest[])
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
	return this->flightNum == cFlightInfo.flightNum;
}

void CFlightInfo::print(ostream& out) const
{
	out << "Flight Info dest: " << this->dest << " Number " << this->flightNum << 
		" minutes " << this->flightMinutes << " KM " << this->destiny << endl;
}
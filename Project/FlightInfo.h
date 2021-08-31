#pragma once
#include "FlightCompException.h"

#define MAX 100

class CFlightInfo
{
private:
	int fNum;
	char dest[MAX];
	int flightMinutes;
	int destiny;

public:
	CFlightInfo(const char dest[], int fNum, int flightMinutes, int destiny) throw(CCompStringException);
	CFlightInfo(const CFlightInfo& other) throw(CCompStringException);

	int getFNum() const;
	const char* getDest() const;
	int getFlightMinutes() const;
	int getDestiny() const;

	void setFNum(int fNum) throw(CCompStringException);
	void setDest(const char* dest) throw(CCompStringException);
	void setFlightMinutes(int flightMinutes) throw(CCompStringException);
	void setDestiny(int destiny) throw(CCompStringException);

	bool isEqual(const CFlightInfo& cFlightInfo);
	void print(ostream& out) const;

	const CFlightInfo& operator=(const CFlightInfo& other) throw(CFlightCompException);
	friend ostream& operator<<(ostream& os, const CFlightInfo& cFlightInfo);
	bool operator==(const CFlightInfo& other) const;
	bool operator!=(const CFlightInfo& other) const;
	operator int() const { return this->flightMinutes; }
};
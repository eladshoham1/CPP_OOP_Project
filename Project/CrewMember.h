#pragma once
#pragma warning(disable : 4290)

//#include "PlaneCrewFactory.h"
#include "FlightCompException.h"

#define MAX_SIZE 100

class CCrewMember
{
protected:
	char* name;
	int flyMinutes;

public:
	CCrewMember(const char* name, int flyMinutes = 0) throw(CCompStringException);
	CCrewMember(ifstream& in);
	CCrewMember(const CCrewMember& cCrewMember) throw(CCompStringException);
	virtual ~CCrewMember();
	const char* getName() const;
	int getFlyMinutes() const;

	void setName(const char* name) throw(CCompStringException);
	void setFlyMinutes(int flyMinutes) throw(CCompStringException);

	virtual void print(ostream& out) const;
	bool isEqual(const CCrewMember& cCrewMember) const;

	virtual void getPresent() const;
	virtual void getUniform() const = 0;
	void takeOff(int minutes) throw(CCompStringException);
	virtual void toOs(ostream& os) const = 0;
	virtual void fromOs(istream& in) { };

	const CCrewMember& operator=(const CCrewMember& other) throw(CCompStringException);
	virtual void operator+=(int minutes) throw(CCompStringException);
	bool operator==(const CCrewMember& other) const;
	friend ostream& operator<<(ostream& os, const CCrewMember& cCrewMember);
	friend istream& operator>>(istream& in, CCrewMember& cCrewMember);
};
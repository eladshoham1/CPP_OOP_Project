#pragma once
#include "FlightCompException.h"

class CPlane
{
protected:
	static int generateNumber;
	int id;
	char* model;
	int seats;

public:
	CPlane(int seats, const char* model) throw(CCompStringException);
	CPlane(ifstream& in);
	CPlane(const CPlane& cPlane) throw(CCompStringException);
	virtual ~CPlane();

	int getId() const;
	char* getModel() const;
	int getSeats() const;

	void setId(int id) throw(CCompStringException);
	void setModel(const char* model) throw(CCompStringException);
	void setSeats(int seats) throw(CCompStringException);

	virtual void toOs(ostream& os) const { }
	virtual void fromOs(istream& os) { }
	void print(ostream& out) const;
	bool isEqual(const CPlane& cPlane);
	virtual void takeOff(int minutes) const { }
	
	const CPlane& operator=(const CPlane& other) throw(CCompStringException);
	friend ostream& operator<<(ostream& os, const CPlane& cPlane);
	friend istream& operator>>(istream& in, CPlane& cPlane);
	const CPlane& operator++();
	CPlane operator++(int);
	bool operator==(const CPlane& other) const;
};
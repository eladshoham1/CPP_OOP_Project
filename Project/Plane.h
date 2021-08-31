#pragma once
#include "FlightCompException.h"

class CPlane
{
protected:
	static int generateNumber;
	int id;
	char* model;
	int numOfChairs;

public:
	CPlane(int numOfChairs, const char* model) throw(CCompStringException);
	CPlane(const CPlane& cPlane) throw(CCompStringException);
	virtual ~CPlane();

	int getId() const;
	char* getModel() const;
	int getNumOfChairs() const;

	void setId(int id) throw(CCompStringException);
	void setModel(const char* model) throw(CCompStringException);
	void setNumOfChairs(int numOfChairs) throw(CCompStringException);

	virtual void toOs(ostream& os) const { };
	void print(ostream& out) const;
	bool isEqual(const CPlane& cPlane);
	virtual void takeOff(int minutes) const { };
	
	const CPlane& operator=(const CPlane& other) throw(CCompStringException);
	friend ostream& operator<<(ostream& os, const CPlane& cPlane);
	const CPlane& operator++();
	CPlane operator++(int);
	bool operator==(const CPlane& other) const;
};
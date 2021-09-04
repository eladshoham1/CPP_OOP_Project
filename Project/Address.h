#pragma once
#pragma warning(disable : 4290)

#include "FlightCompException.h"

class CAddress
{
private:
	char* city;
	char* street;
	int homeNumber;

public:
	CAddress(int homeNumber, const char* street, const char* city = "Tel Aviv") throw (CCompStringException);
	CAddress(ifstream& in);
	CAddress(const CAddress& cAddress) throw (CCompStringException);
	~CAddress();

	char* getCity() const;
	char* getStreet() const;
	int getHomeNumber() const;

	void setCity(const char* city) throw (CCompStringException);
	void setStreet(const char* street) throw (CCompStringException);
	void setHomeNumber(int homeNumber) throw (CCompStringException);

	void updateAddress(const char* city, const char* street, int homeNumber) throw (CCompStringException);

	const CAddress& operator=(const CAddress& other) throw (CCompStringException);
	friend ostream& operator<<(ostream& os, const CAddress& cAddress);
	friend istream& operator>>(istream& in, CAddress& cAddress);
	bool operator==(const CAddress& other) const;
	bool operator!=(const CAddress& other) const;
	const CAddress& getCurrentAddress() const;
};
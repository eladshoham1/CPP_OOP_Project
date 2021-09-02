#pragma once

class CAddress
{
private:
	char* city;
	char* street;
	int homeNumber;

public:
	CAddress(int homeNumber, const char* street, const char* city = "Tel Aviv");
	CAddress(ifstream& in);
	CAddress(const CAddress& cAddress);
	~CAddress();

	char* getCity() const;
	char* getStreet() const;
	int getHomeNumber() const;

	void setCity(const char* city);
	void setStreet(const char* street);
	void setHomeNumber(int homeNumber);

	void updateAddress(const char* city, const char* street, int homeNumber);

	const CAddress& operator=(const CAddress& other);
	friend ostream& operator<<(ostream& os, const CAddress& cAddress);
	friend istream& operator>>(istream& in, CAddress& cAddress);
	bool operator==(const CAddress& other) const;
	bool operator!=(const CAddress& other) const;
	const CAddress& getCurrentAddress() const;
};
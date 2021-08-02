#pragma once
class CAddress
{
private:
	char* city;
	char* street;
	int homeNumber;

public:
	CAddress(int homeNumber, const char* street, const char* city = "tel Aviv");
	~CAddress();

	char* getCity();
	char* getStreet();
	int getHomeNumber();

	void updateAddress(const char* city, const char* street, int homeNumber);
	
	const CAddress& operator=(const CAddress& other);
	friend ostream& operator<<(ostream& os, const CAddress& cAddress);
	friend istream& operator>>(istream& in, CAddress& cAddress);
	bool operator==(const CAddress& other) const;
	bool operator!=(const CAddress& other) const;
	const CAddress& getCurrentAddress();
};


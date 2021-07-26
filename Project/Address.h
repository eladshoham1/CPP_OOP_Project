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

	void print(ostream& out) const;
	void updateAddress(const char* city, const char* street, int homeNumber);
};


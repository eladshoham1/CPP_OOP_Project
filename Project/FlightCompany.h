#pragma once
class CFlightCompany
{
private:
	char* name;

public:
	CFlightCompany(const char* name);
	CFlightCompany(const CFlightCompany& cFlightCompany);
	~CFlightCompany();

	char* getName();
	void setName(const char* name);

	void print(ostream& out) const;

	const CFlightCompany& operator=(const CFlightCompany& other);
};


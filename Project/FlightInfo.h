#pragma once

#define MAX 100

class CFlightInfo
{
private:
	int flightNum;
	char dest[MAX];
	int flightMinutes;
	int destiny;

public:
	CFlightInfo(const char dest[], int flightNum, int flightMinutes, int destiny);

	int getFlightNum();
	char* getDest();
	int getFlightMinutes();
	int getDestiny();

	void setFlightNum(int flightNum);
	void setDest(const char dest[]);
	void setFlightMinutes(int flightMinutes);
	void setDestiny(int destiny);
	
	bool isEqual(const CFlightInfo& cFlightInfo);
	void print(ostream& out) const;
};


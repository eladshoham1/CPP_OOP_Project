#pragma once

#define MAX 100

class CFlightInfo
{
private:
	int fNum;
	char dest[MAX];
	int flightMinutes;
	int destiny;

public:
	CFlightInfo(const char dest[], int fNum, int flightMinutes, int destiny);
	CFlightInfo(const CFlightInfo& other);

	int getFNum() const;
	const char* getDest() const;
	int getFlightMinutes() const;
	int getDestiny() const;

	void setFNum(int fNum);
	void setDest(const char* dest);
	void setFlightMinutes(int flightMinutes);
	void setDestiny(int destiny);

	bool isEqual(const CFlightInfo& cFlightInfo);
	void print(ostream& out) const;

	const CFlightInfo& operator=(const CFlightInfo& other);
	friend ostream& operator<<(ostream& os, const CFlightInfo& cFlightInfo);
	bool operator!=(const CFlightInfo& other) const;
	operator int() const { return this->flightMinutes; }
};
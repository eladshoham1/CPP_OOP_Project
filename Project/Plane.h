#pragma once

class CPlane
{
protected:
	static int generateNumber;
	int id;
	char* model;
	int numOfChairs;

public:
	CPlane(int numOfChairs, const char* model);
	CPlane(const CPlane& cPlane);
	~CPlane();

	int getId() const;
	char* getModel() const;
	int getNumOfChairs() const;

	void setId(int id);
	void setModel(const char* model);
	void setNumOfChairs(int numOfChairs);

	virtual void toOs(ostream& os) const { };
	void print(ostream& out) const;
	bool isEqual(const CPlane& cPlane);
	virtual void takeOff(int minutes) const { };
	
	const CPlane& operator=(const CPlane& other);
	friend ostream& operator<<(ostream& os, const CPlane& cPlane);
	const CPlane& operator++();
	CPlane operator++(int);
	bool operator==(const CPlane& other) const;
};
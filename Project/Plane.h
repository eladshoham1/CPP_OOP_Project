#pragma once
class CPlane
{
private:
	static int generateNumber;
	int id;
	char* model;
	int numOfChairs;

public:
	CPlane(int numOfChairs, const char* model);
	CPlane(const CPlane& cPlane);
	~CPlane();

	int getId();
	char* getModel();
	int getNumOfChairs();

	void print(ostream& out) const;
	bool isEqual(const CPlane& cPlane);

	const CPlane& operator=(const CPlane& other);
	friend ostream& operator<<(ostream& os, const CPlane& cPlane);
	const CPlane& operator++();
	CPlane operator++(int);
};
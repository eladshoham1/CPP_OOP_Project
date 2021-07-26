#pragma once
class CPlane
{
private:
	int id;
	char* model;
	int numOfChairs;

public:
	CPlane(int id, int numOfChairs, const char* model);
	CPlane(const CPlane& cPlane);
	~CPlane();

	int getId();
	char* getModel();
	int getNumOfChairs();

	void print(ostream& out) const;
	bool isEqual(const CPlane& cPlane);
};
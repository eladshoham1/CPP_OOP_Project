#include <iostream>
#include <string.h>
using namespace std;

#include "Plane.h"

int CPlane::generateNumber = 100;

CPlane::CPlane(int numOfChairs, const char* model)
{
	this->id = CPlane::generateNumber++;
	this->numOfChairs = numOfChairs;
	this->model = _strdup(model);
}

CPlane::CPlane(const CPlane& cPlane)
{
	this->id = cPlane.id;
	this->numOfChairs = cPlane.numOfChairs;
	this->model = _strdup(cPlane.model);
}

CPlane::~CPlane()
{
	delete[] this->model;
}

int CPlane::getId()
{
	return this->id;
}


char* CPlane::getModel()
{
	return this->model;
}

int CPlane::getNumOfChairs()
{
	return this->numOfChairs;
}

void CPlane::print(ostream& out) const
{
	out << "Plane " << this->id << " model " << this->model << " seats " << this->numOfChairs << endl;
}

bool CPlane::isEqual(const CPlane& cPlane)
{
	return this->id == cPlane.id;
}

const CPlane& CPlane::operator=(const CPlane& other)
{
	if (this != &other)
	{
		this->id = other.id;
		delete[] this->model;
		this->model = _strdup(other.model);
		this->numOfChairs = other.numOfChairs;
	}

	return *this;
}

ostream& operator<<(ostream& os, const CPlane& cPlane)
{
	os << "Plane " << cPlane.id << " model " << cPlane.model << " seats " << cPlane.numOfChairs << endl;
	return os;
}

const CPlane& CPlane::operator++()
{
	this->numOfChairs++;
	return *this;
}

CPlane CPlane::operator++(int)
{
	return CPlane(this->numOfChairs++, this->model);
}
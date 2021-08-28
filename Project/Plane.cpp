#include <iostream>
using namespace std;
#include <string.h>

#include "Plane.h"

int CPlane::generateNumber = 100;

CPlane::CPlane(int numOfChairs, const char* model) : numOfChairs(numOfChairs)
{
	this->id = CPlane::generateNumber++;
	setModel(model);
}

CPlane::CPlane(const CPlane& cPlane)
{
	*this = cPlane;
}

CPlane::~CPlane()
{
	delete[] this->model;
}

int CPlane::getId() const
{
	return this->id;
}

char* CPlane::getModel() const
{
	return this->model;
}

int CPlane::getNumOfChairs() const
{
	return this->numOfChairs;
}

void CPlane::setId(int id)
{
	this->id = id;
}

void CPlane::setModel(const char* model)
{
	delete[] this->model;
	this->model = _strdup(model);
}

void CPlane::setNumOfChairs(int numOfChairs)
{
	this->numOfChairs = numOfChairs;
}

void CPlane::print(ostream& out) const
{
	out << *this;
}

bool CPlane::isEqual(const CPlane& cPlane)
{
	return this->id == cPlane.id;
}

const CPlane& CPlane::operator=(const CPlane& other)
{
	if (this != &other)
	{
		setId(other.id);
		setModel(other.model);
		setNumOfChairs(other.numOfChairs);
	}

	return *this;
}

ostream& operator<<(ostream& os, const CPlane& cPlane)
{
	os << "Plane " << cPlane.id << " model " << cPlane.model << " seats " << cPlane.numOfChairs << endl;
	cPlane.toOs(os);
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
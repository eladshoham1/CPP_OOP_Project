#include <iostream>
using namespace std;
#include <string.h>

#include "Plane.h"

int CPlane::generateNumber = 100;

CPlane::CPlane(int numOfChairs, const char* model) throw(CCompStringException) : numOfChairs(numOfChairs)
{
	this->id = CPlane::generateNumber++;
	setModel(model);
}

CPlane::CPlane(const CPlane& cPlane) throw(CCompStringException)
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

void CPlane::setId(int id) throw(CCompStringException)
{
	if (id < 0)
		throw("Id must be positive number");

	this->id = id;
}

void CPlane::setModel(const char* model) throw(CCompStringException)
{
	if (strcmp(model, "") == 0)
		throw("Model can't be empty");

	delete[] this->model;
	this->model = _strdup(model);
}

void CPlane::setNumOfChairs(int numOfChairs) throw(CCompStringException)
{
	if (numOfChairs < 0)
		throw("Number of chairs must be positive number");

	this->numOfChairs = numOfChairs;
}

void CPlane::print(ostream& out) const
{
	out << *this;
}

bool CPlane::isEqual(const CPlane& cPlane)
{
	return *this == cPlane;
}

const CPlane& CPlane::operator=(const CPlane& other) throw(CCompStringException)
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

bool CPlane::operator==(const CPlane& other) const
{
	return this->id == other.id;
}
#include <iostream>
#include <string.h>
using namespace std;

#include "Plane.h"

CPlane::CPlane(int id, int numOfChairs, const char* model)
{
	this->id = id;
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
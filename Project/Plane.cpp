#include <fstream>
using namespace std;
#include <string.h>

#include "Plane.h"

int CPlane::generateNumber = 100;

CPlane::CPlane(int seats, const char* model)
{
	this->id = CPlane::generateNumber++;
	setSeats(seats);
	setModel(model);
}

CPlane::CPlane(ifstream& in)
{
	in >> *this;
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

int CPlane::getSeats() const
{
	return this->seats;
}

void CPlane::setId(int id)
{
	if (id < 0)
		throw CCompStringException("Id must be positive number");

	this->id = id;
}

void CPlane::setModel(const char* model)
{
	if (strcmp(model, "") == 0)
		throw CCompStringException("Model can't be empty");

	delete[] this->model;
	this->model = _strdup(model);
}

void CPlane::setSeats(int seats)
{
	if (seats < 0)
		throw CCompStringException("Number of seats must be positive number");

	this->seats = seats;
}

void CPlane::print(ostream& out) const
{
	out << *this;
}

bool CPlane::isEqual(const CPlane& cPlane)
{
	return *this == cPlane;
}

const CPlane& CPlane::operator=(const CPlane& other)
{
	if (this != &other)
	{
		setId(other.id);
		setModel(other.model);
		setSeats(other.seats);
	}

	return *this;
}

ostream& operator<<(ostream& os, const CPlane& cPlane)
{
	if (typeid(os) == typeid(ofstream))
		os << cPlane.id << " " << cPlane.model << " " << cPlane.seats << endl;
	else
		os << "Plane " << cPlane.id << " model " << cPlane.model << " seats " << cPlane.seats << endl;

	cPlane.toOs(os);
	return os;
}

istream& operator>>(istream& in, CPlane& cPlane)
{
	delete[] cPlane.model;
	cPlane.model = new char[100];

	if (typeid(in) == typeid(ifstream))
		in >> cPlane.id >> cPlane.model >> cPlane.seats;
	else
	{
		/*cout << "\nPlease enter model: ";
		in.getline(cPlane.model, MAX);

		cout << "\nPlease enter number of chairs: ";
		in >> cPlane.seats;*/
	}

	cPlane.fromOs(in);
	return in;
}

const CPlane& CPlane::operator++()
{
	this->seats++;
	return *this;
}

CPlane CPlane::operator++(int)
{
	return CPlane(this->seats++, this->model);
}

bool CPlane::operator==(const CPlane& other) const
{
	return this->id == other.id;
}
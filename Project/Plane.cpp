#include <fstream>
using namespace std;
#include <string.h>

#include "Plane.h"

int CPlane::generateNumber = 100;

CPlane::CPlane(int seats, const char* model) throw(CCompStringException) : seats(seats)
{
	this->id = CPlane::generateNumber++;
	setModel(model);
}

CPlane::CPlane(ifstream& in)
{
	in >> *this;
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

int CPlane::getSeats() const
{
	return this->seats;
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

void CPlane::setSeats(int seats) throw(CCompStringException)
{
	if (seats < 0)
		throw("Number of seats must be positive number");

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

const CPlane& CPlane::operator=(const CPlane& other) throw(CCompStringException)
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
		os << (typeid(cPlane) == typeid(CPlane) ? 0 : 1) << cPlane.id << " " << cPlane.model << " " << cPlane.seats << endl;
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
		in >> CPlane::generateNumber >> cPlane.id >> cPlane.model >> cPlane.seats;
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
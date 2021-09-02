#include <fstream>
using namespace std;

#include "Cargo.h"

CCargo::CCargo (int numOfChairs, const char* model, float maxWeight, float maxVolume) throw(CCompStringException) : CPlane(numOfChairs, model)
{
	setMaxWeight(maxWeight);
	setMaxVolume(maxVolume);
	setCurrentWeight(0.f);
	setCurrentVolume(0.f);
}

CCargo::CCargo(ifstream& in) : CPlane(in)
{
	fromOs(in);
}

CCargo::CCargo(const CCargo& cCargo) throw(CCompStringException) : CPlane(cCargo)
{
	setMaxWeight(cCargo.maxWeight);
	setMaxVolume(cCargo.maxVolume);
	setCurrentWeight(cCargo.currentWeight);
	setCurrentVolume(cCargo.currentVolume);
}

void CCargo::setMaxWeight(float maxWeight) throw(CCompStringException)
{
	if (maxWeight < 0)
		throw("Max weight must be positive number");

	this->maxWeight = maxWeight;
}

void CCargo::setMaxVolume(float maxVolume) throw(CCompStringException)
{
	if (maxVolume < 0)
		throw("Max volume must be positive number");

	this->maxVolume = maxVolume;
}

void CCargo::setCurrentWeight(float currentWeight) throw(CCompStringException)
{
	if (currentWeight < 0)
		throw("Current volume must be positive number");

	this->currentWeight = currentWeight;
}

void CCargo::setCurrentVolume(float currentVolume) throw(CCompStringException)
{
	if (currentVolume < 0)
		throw("Current volume must be positive number");

	this->currentVolume = currentVolume;
}

void CCargo::load(float weight, float volume) throw(CCompStringException)
{
	if (this->currentVolume + volume > this->maxVolume)
		throw("There is not enough volume on the plane for this volume");

	if (this->currentWeight + weight > this->maxWeight)
		throw("There is not enough weight on the plane for this weight");

	setCurrentVolume(this->currentVolume + volume);
	setCurrentWeight(this->currentWeight + weight);
}

void CCargo::takeOff(int minutes) const
{
	cout << "Need to add " << minutes << " minutes to my log book" << endl;
}

void CCargo::toOs(ostream& os) const
{
	if (typeid(os) == typeid(ofstream))
		os << endl << this->maxVolume << " " << this->maxWeight << "  " << this->currentVolume << " " << this->currentWeight << endl;
	else
		os << "Cargo " << "M_vol " << this->maxVolume << " M_Kg " << this->maxWeight << " C_vol "
		<< this->currentVolume << " C_Kg " << this->currentWeight << endl;
}

void CCargo::fromOs(istream& in)
{
	if (typeid(in) == typeid(ifstream))
		in >> this->maxVolume >> this->maxWeight >> this->currentVolume >> this->currentWeight;
	else
	{
		cout << "\nPlease enter max weight: ";
		in >> this->maxWeight;
		cout << "\nPlease enter max volume: ";
		in >> this->maxVolume;
	}
}
#include <iostream>
using namespace std;

#include "Cargo.h"

CCargo::CCargo (int numOfChairs, const char* model, float maxWeight, float maxVolume) : CPlane(numOfChairs, model)
{
	setMaxWeight(maxWeight);
	setMaxVolume(maxVolume);
	setCurrentWeight(0.f);
	setCurrentVolume(0.f);
}

void CCargo::setMaxWeight(float maxWeight)
{
	this->maxWeight = maxWeight;
}

void CCargo::setMaxVolume(float maxVolume)
{
	this->maxVolume = maxVolume;
}

void CCargo::setCurrentWeight(float currentWeight)
{
	this->currentWeight = currentWeight;
}

void CCargo::setCurrentVolume(float currentVolume)
{
	this->currentVolume = currentVolume;
}

bool CCargo::load(float weight, float volume)
{
	if (this->currentVolume + volume <= this->maxVolume && this->currentWeight + weight <= this->maxWeight)
	{
		setCurrentVolume(this->currentVolume + volume);
		setCurrentWeight(this->currentWeight + weight);

		return true;
	}

	return false;
}

void CCargo::takeOff(int minutes) const
{
	cout << "Need to add " << minutes << " to my log book" << endl;
}

void CCargo::toOs(ostream& os) const
{
	os << "Cargo " << "M_vol " << this->maxVolume << " M_Kg " << this->maxWeight << " C_vol " 
		<< this->currentVolume << " C_Kg " << this->currentWeight << endl;
}
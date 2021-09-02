#pragma once
#include "FlightCompException.h"
#include "Plane.h"

class CCargo : public CPlane
{
private:
	float maxWeight;
	float maxVolume;
	float currentWeight;
	float currentVolume;

public:
	CCargo(int numOfChairs, const char* model, float maxWeight, float maxVolume) throw(CCompStringException);
	CCargo(ifstream& in);
	CCargo(const CCargo& cCargo) throw(CCompStringException);

	void setMaxWeight(float maxWeight) throw(CCompStringException);
	void setMaxVolume(float maxVolume) throw(CCompStringException);
	void setCurrentWeight(float currentWeight) throw(CCompStringException);
	void setCurrentVolume(float currentVolume) throw(CCompStringException);

	void load(float weight, float volume) throw(CCompStringException);
	virtual void takeOff(int minutes) const override;
	virtual void toOs(ostream& os) const override;
	virtual void fromOs(istream& in) override;
};


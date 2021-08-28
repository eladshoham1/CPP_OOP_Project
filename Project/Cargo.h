#pragma once

#include "Plane.h"

class CCargo : public CPlane
{
private:
	float maxWeight;
	float maxVolume;
	float currentWeight;
	float currentVolume;

public:
	CCargo(int numOfChairs, const char* model, float maxWeight, float maxVolume);

	void setMaxWeight(float maxWeight);
	void setMaxVolume(float maxVolume);
	void setCurrentWeight(float currentWeight);
	void setCurrentVolume(float currentVolume);

	bool load(float weight, float volume);
	virtual void takeOff(int minutes) const override;
	virtual void toOs(ostream& os) const override;
};


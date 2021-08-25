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

	bool load(float volume, float weight);
	void taskOffMessage(int minutes);
};


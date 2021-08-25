#pragma once

#include "CrewMember.h"

class CHost : public CCrewMember
{
public:
	enum type { eRegular, eSuper, eCalcelan };

private:
	type hostType;

public:
	CHost(const char* name, type hostType, int flyMinutes = 0);
	CHost(const CHost& cHost);

	void setHostType(type hostType);

	virtual void getPresent() const override;
	virtual void getUniform() const override;
};


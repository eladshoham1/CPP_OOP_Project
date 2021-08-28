#pragma once

#include "CrewMember.h"
#include "Address.h"

class CPilot : public CCrewMember
{
private:
	bool isCaptain;
	CAddress *homeAddress;

public:
	CPilot(const char *name, bool isCaptain, CAddress *homeAddress = nullptr, int flyMinutes = 0);
	CPilot(const CPilot& cPilot);
	virtual ~CPilot();

	void setIsCaptain(bool isCaptain);
	void setHomeAddress(CAddress *homeAddress);

	void toSimulator() const;
	virtual void getUniform() const override;
	virtual void print(ostream& out) const override;
	virtual void toOs(ostream& os) const override;

	virtual bool operator+=(int minutes);
};


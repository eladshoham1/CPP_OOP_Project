#pragma once
#pragma warning(disable : 4290)

#include "CrewMember.h"
#include "Address.h"

class CPilot : public CCrewMember
{
private:
	bool isCaptain;
	CAddress *homeAddress;

public:
	CPilot(const char *name, bool isCaptain, CAddress *homeAddress = nullptr, int flyMinutes = 0) throw(CCompStringException);
	CPilot(ifstream& in);
	CPilot(const CPilot& cPilot) throw(CCompStringException);
	~CPilot();

	void setIsCaptain(bool isCaptain);
	void setHomeAddress(CAddress *homeAddress) throw(CCompStringException);

	void toSimulator() const;
	virtual void getUniform() const override;
	virtual void print(ostream& out) const override;
	virtual void toOs(ostream& os) const override;
	virtual void fromOs(istream& in) override;

	virtual void operator+=(int minutes) throw(CCompStringException);;
};


#pragma once

#include "CrewMember.h"

class CHost : public CCrewMember
{
public:
	enum eType { eRegular, eSuper, eCalcelan };
	const char* types[3] = { "Regular", "Super", "Calcelan" };

private:
	eType hostType;

public:
	CHost(const char* name, eType hostType, int flyMinutes = 0) throw(CCompStringException);;
	CHost(ifstream& in);
	CHost(const CHost& cHost) throw(CCompStringException);;

	eType getHostType() const;
	void setHostType(eType hostType) throw(CCompStringException);

	virtual void getPresent() const override;
	virtual void getUniform() const override;
	virtual void toOs(ostream& os) const override;
	virtual void fromOs(istream& in) override;
};


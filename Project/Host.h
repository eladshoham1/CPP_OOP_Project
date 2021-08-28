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
	CHost(const char* name, eType hostType, int flyMinutes = 0);
	CHost(const CHost& cHost);

	eType getHostType() const;
	void setHostType(eType hostType);

	virtual void getPresent() const override;
	virtual void getUniform() const override;
	virtual void toOs(ostream& os) const override;
};


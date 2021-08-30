#pragma once

class CCrewMember
{
protected:
	char* name;
	int flyMinutes;

public:
	CCrewMember(const char* name, int flyMinutes = 0);
	CCrewMember(const CCrewMember& cCrewMember);
	/* virtual */ ~CCrewMember();
	const char* getName() const;
	int getFlyMinutes() const;

	void setName(const char* name);
	void setFlyMinutes(int flyMinutes);

	virtual void print(ostream& out) const;
	bool isEqual(const CCrewMember& cCrewMember) const;

	virtual void getPresent() const;
	virtual void getUniform() const = 0;
	void takeOff(int minutes);
	virtual void toOs(ostream& os) const = 0;

	const CCrewMember& operator=(const CCrewMember& other);
	virtual bool operator+=(int minutes);
	bool operator==(const CCrewMember& other) const;
	friend ostream& operator<<(ostream& os, const CCrewMember& cCrewMember);
};
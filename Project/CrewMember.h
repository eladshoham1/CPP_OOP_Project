#pragma once
class CCrewMember
{
private:
	char* name;
	int flyMinutes;
	
public:
	CCrewMember(const char* name, int flyMinutes = 0);
	CCrewMember(const CCrewMember& cCrewMember);
	~CCrewMember();
	bool updateMinutes(int minutes);
	char* getName();
	void setName(const char* name);
	int getFlyMinutes();
	void print(ostream& out) const;
	bool isEqual(const CCrewMember& cCrewMember);
};


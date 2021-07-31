#pragma once
class CCrewMember
{
private:
	static int generateNumber;
	int workerId;
	char* name;
	int flyMinutes;
	
public:
	CCrewMember(const char* name, int flyMinutes = 0);
	CCrewMember(const CCrewMember& cCrewMember);
	~CCrewMember();

	char* getName();
	void setName(const char* name);
	int getFlyMinutes();

	void print(ostream& out) const;
	bool isEqual(const CCrewMember& cCrewMember);

	const CCrewMember& operator=(const CCrewMember& other);
	const CCrewMember& operator+=(int minutes);
	bool operator==(const CCrewMember& other) const;
};


#pragma once
class CCrewMember
{
public:
	static int generateID;
	static constexpr int START_ID = 1000;
private:
	int workerId;
	char* name;
	int flyMinutes;
	
public:
	CCrewMember(const char* name, int flyMinutes = 0);
	CCrewMember(const CCrewMember& cCrewMember);
	CCrewMember(CCrewMember&& cCrewMember);
	~CCrewMember();

	int getWorkerId() const;
	char* getName();
	void setName(const char* name);
	int getFlyMinutes();

	void print(ostream& out) const;
	bool isEqual(const CCrewMember& cCrewMember);

	const CCrewMember& operator=(const CCrewMember& other);
	bool operator+=(int minutes);
	bool operator==(const CCrewMember& other) const;
};


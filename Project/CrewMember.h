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
	~CCrewMember();

	int getWorkerId() const;
	const char* getName() const;
	int getFlyMinutes() const;

	void setWorkerId(int workerId);
	void setName(const char* name);
	void setFlyMinutes(int flyMinutes);

	void print(ostream& out) const;
	bool isEqual(const CCrewMember& cCrewMember) const;

	const CCrewMember& operator=(const CCrewMember& other);
	bool operator+=(int minutes);
	bool operator==(const CCrewMember& other) const;
	friend ostream& operator<<(ostream& os, const CCrewMember& cCrewMember);
};
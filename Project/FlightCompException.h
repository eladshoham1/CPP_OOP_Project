#pragma once

#include <iostream>
using namespace std;

class CFlightCompException
{
public:
	virtual void show() const = 0;
};

class CCompStringException : public CFlightCompException
{
private:
	char* msg;
public:

	CCompStringException(const char* msg) 
	{
		this->msg = _strdup(msg);
	}

	virtual void show() const override
	{
		cout << msg << endl;
	}
};

class CCompLimitException : public CFlightCompException
{
private:
	int max;
public:

	CCompLimitException(int max) : max(max) {}

	virtual void show() const override
	{
		cout << "Index out of boundry, ";

		if (max == 0)
			cout << "there is no elements" << endl;
		else
			cout << max << " is the maximum" << endl;
	}
};

class CCompFileException : public CFlightCompException
{
private:
	char* fileName;
public:

	CCompFileException(const char* fileName)
	{
		this->fileName = _strdup(fileName);
	}

	virtual void show() const override
	{
		cout << "There is a problem with the file " << fileName << endl;
	}
};
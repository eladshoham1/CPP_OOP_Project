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
protected:
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
		cout << "Index out of boundry, the number of elements is " << max << endl;
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

class CCompInputTypeException : public CCompStringException
{
private:
	istream& in;
	static constexpr int MAX_SIZE = 256;
public:
	CCompInputTypeException(istream& in) : CCompStringException("Wrong input type"), in(in) {}

	virtual void show() const override
	{
		CCompStringException::show();
		in.clear();
		in.ignore(MAX_SIZE, '\n');
	}
};
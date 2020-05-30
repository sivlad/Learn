#pragma once

#ifndef CMONITOREDPARAM_H
#define CMONITOREDPARAM_H

#include <vector>
#include "CValues.h"

class CMonitoredParam
{
public:
	char* FName;
	char* FSNMPComand;
	char* FLogfileName;
	std::vector<CValues*> FValues;

	CMonitoredParam();
	~CMonitoredParam();
	virtual void AddCValues();
	virtual void SaveCValues(CValues* aValues);
	virtual void AddCValues(char* aDate, char* aTime, long int aValue);
	virtual void LoadValues();
	virtual void CountDelta();
	virtual void CountDelta(int aPos);


};


#endif
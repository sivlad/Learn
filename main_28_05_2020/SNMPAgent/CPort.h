#pragma once

#ifndef CPORT_H
#define CPORT_H

#include <vector>
#include "CMonitoredParam.h"

class CMonitoredParam;

class CPort
{
public :
	char* FName;

	std::vector<CMonitoredParam*> FMonitoredParam;

	CPort();
	~CPort();
	virtual void AddMonitoredParam();
	virtual void SaveMonitoredParam(CMonitoredParam* aMonitoredParam);
	virtual void AddMonitoredParam(char* aName, char* aConectionString, char* aLogfileName);

};

#endif
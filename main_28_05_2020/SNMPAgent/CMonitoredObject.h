#ifndef CCMONITOREDOBJECT_H
#define CCMONITOREDOBJECT_H


#pragma once
#include <vector>
#include "CPort.h"


class CPort;

class CMonitoredObject
{
public:
	char* FName;
	char* FIpAdress;
	char* FVersionSNMP;
	char* FConectionString;

	std::vector<CPort*> FMonitoredInstance;

	CMonitoredObject();
	~CMonitoredObject();
	virtual void AddMonitoredInstance();
	virtual void SaveConfMonitoredInstance(CPort* aPort);
	virtual void AddMonitoredInstance(char* aName);
};


#endif
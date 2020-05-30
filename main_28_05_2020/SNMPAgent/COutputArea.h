#pragma once

#ifndef COUTPUTAREA_H
#define COUTPUTAREA_H

#include "CInputOutpuForm.h"
#include "CMonitoredObject.h"


class COutputArea :
	public CInputOutpuForm
{
public:
	virtual void FormDraw(HDC aHdcDest);
	virtual void FormTextOut(HDC aHdcDest, CMonitoredObject* aMonitoredObject);
};


#endif
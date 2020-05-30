#pragma once

#ifndef CLABEL_H
#define CLABEL_H

#include "CInputOutpuForm.h"

class CLabel :
	public CInputOutpuForm
{
public:

	CLabel();
	~CLabel();

	virtual void FormCreate();
	virtual void FormShow(HDC aOutputDC);
	virtual void FormDraw();
	virtual void FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC);

};


#endif
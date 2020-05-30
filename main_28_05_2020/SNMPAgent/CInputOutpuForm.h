#pragma once

#ifndef CINPUTOUTPUTFORM_H
#define CINPUTOUTPUTFORM_H

#include <Windows.h>

class CInputOutpuForm
{
public:
	char* FName;
	char* FCaaption;
	RECT FPosition;
	int FWidth;
	int FHeight;
	bool FVisible;
	bool FPresseed;

	CInputOutpuForm();
	~CInputOutpuForm();
	virtual void FormCreate();
	virtual void FormShow(HDC aOutputDC);
	virtual void FormDraw();
	virtual void FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC);

};



#endif

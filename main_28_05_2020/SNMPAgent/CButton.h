#pragma once

#ifndef CBUTTON_H
#define CBUTTON_H

#include "CInputOutpuForm.h"

class Application;
class CButton;

typedef void(*FuncOnKey_Button)(CButton* Sender, Application* App_Sender);


class CButton :
	public CInputOutpuForm
{
public:

	FuncOnKey_Button OnButtonClick;

	virtual void FormCreate();
	virtual void FormShow(HDC aOutputDC);
	virtual void FormDraw();
	virtual void FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC);

	virtual void DoOnButtonClick(Application* Sender);

};

#endif
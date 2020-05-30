#pragma once

#ifndef CTEXTINPUTBOX_H
#define CTEXTINPUTBOX_H

#include "CInputOutpuForm.h"

class Application;
class CTextInputBox;

typedef void(*FuncOnKey_TextInputBox)(CTextInputBox* Sender, Application* App_Sender);


class CTextInputBox :
	public CInputOutpuForm

{
public:

	FuncOnKey_TextInputBox OnTextInput;

	virtual void FormCreate();
	virtual void FormShow(HDC aOutputDC);
	virtual void FormDraw();
	virtual void FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC);

	virtual void DoOnTextInput(Application* Sender);

};

#endif
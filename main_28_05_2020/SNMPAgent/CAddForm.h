#pragma once

#ifndef CADDFORM_H
#define CADDFORM_H

#include "CInputOutpuForm.h"
#include "CLabel.h"
#include "CButton.h"
#include "CTextInputBox.h"
#include "COutputArea.h"



class Application;

class CAddForm :
	public CInputOutpuForm
{
public:

	HDC Addform;
	HBITMAP AddformBitmap;

	CLabel*          FDeviceLabel1;
	CLabel*          FDeviceLabel2;
	CLabel*          FDeviceLabel3;
	CLabel*			 FDeviceLabel4;
	CLabel*			 FDeviceLabel5;
	CLabel*			 FDeviceLabel6;
	CTextInputBox*   FDeviceTextBox1;
	CTextInputBox*   FDeviceTextBox2;
	CTextInputBox*   FDeviceTextBox3;
	CTextInputBox*   FDeviceTextBox4;
	CTextInputBox*   FDeviceTextBox5;
	CTextInputBox*   FDeviceTextBox6;
	CButton*         FOkButton;
	CButton*         FCancelButton;
	CButton*         FOkButtonDevice;
	CButton*         FOkButtonInterface;
	CButton*         FOkButtonParametr;
	COutputArea*     FOutputAreaTreeOutput;


	CAddForm();
	~CAddForm();

	virtual void FormCreate(Application* Sender);
	virtual void FormShow(HDC aOutputDC);
	virtual void FormDraw(Application* Sender);
	virtual void FormLoadPeram(Application* Sender);


};


#endif
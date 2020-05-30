#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include "../StringHelper.h"
#include "CAddForm.h"
#include "../Application.h"


#include "..\StringHelper.h"


CAddForm::CAddForm() {

	FDeviceLabel1 = new CLabel();
	FDeviceLabel2 = new CLabel();
	FDeviceLabel3 = new CLabel();
	FDeviceLabel4 = new CLabel();
	FDeviceLabel5 = new CLabel();
	FDeviceLabel6 = new CLabel();
	FDeviceTextBox1 = new CTextInputBox();
	FDeviceTextBox2 = new CTextInputBox();
	FDeviceTextBox3 = new CTextInputBox();
	FDeviceTextBox4 = new CTextInputBox();
	FDeviceTextBox5 = new CTextInputBox();
	FDeviceTextBox6 = new CTextInputBox();
	FOkButton = new CButton();
	FCancelButton = new CButton();
	FOkButtonDevice = new CButton();
	FOkButtonInterface = new CButton();
	FOkButtonParametr = new CButton();
	FOutputAreaTreeOutput = new COutputArea();

}

CAddForm::~CAddForm() {
	delete(FDeviceLabel1);
	delete(FDeviceLabel2);
	delete(FDeviceLabel3);
	delete(FDeviceLabel4);
	delete(FDeviceLabel5);
	delete(FDeviceLabel6);
	delete(FDeviceTextBox1);
	delete(FDeviceTextBox2);
	delete(FDeviceTextBox3);
	delete(FDeviceTextBox4);
	delete(FDeviceTextBox5);
	delete(FDeviceTextBox6);
	delete(FOkButton);
	delete(FCancelButton);
	delete(FOkButtonDevice);
	delete(FOkButtonInterface);
	delete(FOkButtonParametr);
	delete(FOutputAreaTreeOutput);
	delete(AddformBitmap);
	ReleaseDC(GetConsoleWindow(), Addform);

}


void CAddForm::FormLoadPeram(Application* Sender) {
	for (CMapObjectItem* LMapObjectItem : Sender->MapObject) {
		if (0 == strcmp(LMapObjectItem->FName, "DeviceLabel1")) {
			strcpy_s(FDeviceLabel1->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceLabel1->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceLabel1->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceLabel1->FWidth = LMapObjectItem->FWidth;
			FDeviceLabel1->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceLabel1->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceLabel2")) {
			strcpy_s(FDeviceLabel2->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceLabel2->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceLabel2->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceLabel2->FWidth = LMapObjectItem->FWidth;
			FDeviceLabel2->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceLabel2->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceLabel3")) {
			strcpy_s(FDeviceLabel3->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceLabel3->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceLabel3->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceLabel3->FWidth = LMapObjectItem->FWidth;
			FDeviceLabel3->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceLabel3->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceLabel4")) {
			strcpy_s(FDeviceLabel4->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceLabel4->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceLabel4->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceLabel4->FWidth = LMapObjectItem->FWidth;
			FDeviceLabel4->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceLabel4->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceLabel5")) {
			strcpy_s(FDeviceLabel5->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceLabel5->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceLabel5->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceLabel5->FWidth = LMapObjectItem->FWidth;
			FDeviceLabel5->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceLabel5->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceLabel6")) {
			strcpy_s(FDeviceLabel6->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceLabel6->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceLabel6->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceLabel6->FWidth = LMapObjectItem->FWidth;
			FDeviceLabel6->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceLabel6->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceTextBox1")) {
			strcpy_s(FDeviceTextBox1->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceTextBox1->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceTextBox1->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceTextBox1->FWidth = LMapObjectItem->FWidth;
			FDeviceTextBox1->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceTextBox1->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceTextBox2")) {
			strcpy_s(FDeviceTextBox2->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceTextBox2->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceTextBox2->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceTextBox2->FWidth = LMapObjectItem->FWidth;
			FDeviceTextBox2->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceTextBox2->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceTextBox3")) {
			strcpy_s(FDeviceTextBox3->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceTextBox3->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceTextBox3->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceTextBox3->FWidth = LMapObjectItem->FWidth;
			FDeviceTextBox3->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceTextBox3->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceTextBox6")) {
			strcpy_s(FDeviceTextBox6->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceTextBox6->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceTextBox6->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceTextBox6->FWidth = LMapObjectItem->FWidth;
			FDeviceTextBox6->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceTextBox6->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceTextBox4")) {
			strcpy_s(FDeviceTextBox4->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceTextBox4->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceTextBox4->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceTextBox4->FWidth = LMapObjectItem->FWidth;
			FDeviceTextBox4->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceTextBox4->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "DeviceTextBox5")) {
			strcpy_s(FDeviceTextBox5->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FDeviceTextBox5->FPosition.left = LMapObjectItem->FPosition.left;
			FDeviceTextBox5->FPosition.top = LMapObjectItem->FPosition.top;
			FDeviceTextBox5->FWidth = LMapObjectItem->FWidth;
			FDeviceTextBox5->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FDeviceTextBox5->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "OkButton")) {
			strcpy_s(FOkButton->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FOkButton->FPosition.left = LMapObjectItem->FPosition.left;
			FOkButton->FPosition.top = LMapObjectItem->FPosition.top;
			FOkButton->FWidth = LMapObjectItem->FWidth;
			FOkButton->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FOkButton->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "CancelButton")) {
			strcpy_s(FCancelButton->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FCancelButton->FPosition.left = LMapObjectItem->FPosition.left;
			FCancelButton->FPosition.top = LMapObjectItem->FPosition.top;
			FCancelButton->FWidth = LMapObjectItem->FWidth;
			FCancelButton->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FCancelButton->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "OkButtonDevice")) {
			strcpy_s(FOkButtonDevice->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FOkButtonDevice->FPosition.left = LMapObjectItem->FPosition.left;
			FOkButtonDevice->FPosition.top = LMapObjectItem->FPosition.top;
			FOkButtonDevice->FWidth = LMapObjectItem->FWidth;
			FOkButtonDevice->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FOkButtonDevice->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "OkButtonInterface")) {
			strcpy_s(FOkButtonInterface->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FOkButtonInterface->FPosition.left = LMapObjectItem->FPosition.left;
			FOkButtonInterface->FPosition.top = LMapObjectItem->FPosition.top;
			FOkButtonInterface->FWidth = LMapObjectItem->FWidth;
			FOkButtonInterface->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FOkButtonInterface->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "OkButtonParametr")) {
			strcpy_s(FOkButtonParametr->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FOkButtonParametr->FPosition.left = LMapObjectItem->FPosition.left;
			FOkButtonParametr->FPosition.top = LMapObjectItem->FPosition.top;
			FOkButtonParametr->FWidth = LMapObjectItem->FWidth;
			FOkButtonParametr->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FOkButtonParametr->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
		if (0 == strcmp(LMapObjectItem->FName, "OutputAreaTreeOutput")) {
			strcpy_s(FOutputAreaTreeOutput->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			FOutputAreaTreeOutput->FPosition.left = LMapObjectItem->FPosition.left;
			FOutputAreaTreeOutput->FPosition.top = LMapObjectItem->FPosition.top;
			FOutputAreaTreeOutput->FPosition.right = LMapObjectItem->FPosition.right;
			FOutputAreaTreeOutput->FPosition.bottom = LMapObjectItem->FPosition.bottom;
			FOutputAreaTreeOutput->FWidth = LMapObjectItem->FWidth;
			FOutputAreaTreeOutput->FHeight = LMapObjectItem->FHeight;
			strcpy_s(FOutputAreaTreeOutput->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}
	}


}


void CAddForm::FormCreate(Application* Sender) {

	for (CMapObjectItem* LMapObjectItem : Sender->MapObject) {
		if (0 == strcmp(LMapObjectItem->FName, "AddForm")) {
			strcpy_s(this->FName, StringHelper::DefaultBufferSize, LMapObjectItem->FName);
			this->FPosition.left = LMapObjectItem->FPosition.left;
			this->FPosition.top = LMapObjectItem->FPosition.top;
			this->FPosition.right = LMapObjectItem->FPosition.right;
			this->FPosition.bottom = LMapObjectItem->FPosition.bottom;
			this->FWidth = LMapObjectItem->FWidth;
			this->FHeight = LMapObjectItem->FHeight;
			strcpy_s(this->FCaaption, StringHelper::DefaultBufferSize, LMapObjectItem->FCaption);
		}

	}

	HDC localdc = GetDC(GetConsoleWindow());

	Addform = CreateCompatibleDC(localdc);
	AddformBitmap = CreateCompatibleBitmap(localdc, FWidth, FHeight);
	SelectObject(Addform, AddformBitmap);
}

void CAddForm::FormShow(HDC aOutputDC) {

	BitBlt(aOutputDC, FPosition.left, FPosition.top, FWidth, FWidth, Addform, 0, 0, SRCCOPY);

}

void CAddForm::FormDraw(Application* Sender) {
	HDC localdc = GetDC(GetConsoleWindow());

	HBRUSH LBrush = CreateSolidBrush(RGB(185, 212, 231));
	HBRUSH LOldBrush = (HBRUSH)SelectObject(Addform, LBrush);
	Rectangle(Addform,0, 0, FWidth, FHeight);

	FDeviceLabel1->FormDraw(Addform, Sender->MainformNotPressed, { 590,100 });
	FDeviceLabel2->FormDraw(Addform, Sender->MainformNotPressed, { 590,100 });
	FDeviceLabel3->FormDraw(Addform, Sender->MainformNotPressed, { 590,100 });
	FDeviceLabel4->FormDraw(Addform, Sender->MainformNotPressed, { 590,100 });
	FDeviceLabel5->FormDraw(Addform, Sender->MainformNotPressed, { 590,100 });
	FDeviceLabel6->FormDraw(Addform, Sender->MainformNotPressed, { 590,100 });

	FDeviceTextBox1->FormDraw(Addform, Sender->MainformNotPressed, { 820,100 });
	FDeviceTextBox2->FormDraw(Addform, Sender->MainformNotPressed, { 820,100 });
	FDeviceTextBox3->FormDraw(Addform, Sender->MainformNotPressed, { 820,100 });
	FDeviceTextBox4->FormDraw(Addform, Sender->MainformNotPressed, { 820,100 });
	FDeviceTextBox5->FormDraw(Addform, Sender->MainformNotPressed, { 820,100 });
	FDeviceTextBox6->FormDraw(Addform, Sender->MainformNotPressed, { 820,100 });

	FOkButton->FormDraw(Addform, Sender->MainformNotPressed, { 910,160 });
	FOkButtonDevice->FormDraw(Addform, Sender->MainformNotPressed, { 910,160 });
	FOkButtonInterface->FormDraw(Addform, Sender->MainformNotPressed, { 910,160 });
	FOkButtonParametr->FormDraw(Addform, Sender->MainformNotPressed, { 910,160 });
	FCancelButton->FormDraw(Addform, Sender->MainformNotPressed, { 730,160 });

	FOutputAreaTreeOutput->FormDraw(Addform);
	if (NULL != Sender->FAddedMonitoredObject) {
		FOutputAreaTreeOutput->FormTextOut(Addform, Sender->FAddedMonitoredObject);
	}

}

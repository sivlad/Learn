#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Console.h"
#include "Application.h"
#include <stdio.h>
#include "StringHelper.h"
#include "SNMPAgent/CMonitoredObject.h"
#include "SNMPAgent/CMapObjectItem.h"
#include "SNMPAgent/CInputOutpuForm.h"
#include "SNMPAgent/CTextInputBox.h"

#include <string.h>
#include <time.h>

void TextInputBox_OnTextInput(CTextInputBox* Sender, Application* App_Sender);
void OkButtonDevice_OnButtonClick(CButton* Sender, Application* App_Sender);
void OkButtonInterface_OnButtonClick(CButton* Sender, Application* App_Sender);
void OkButtonParametr_OnButtonClick(CButton* Sender, Application* App_Sender);
void CancelButton_OnButtonClick(CButton* Sender, Application* App_Sender);
void OkButton_OnButtonClick(CButton* Sender, Application* App_Sender);


Application::Application() {
	// установка локализации по-умолчанию
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// установка параметров экрана по-умолчанию
	Console::SetScreen();

	// очистим экран
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width() );
	// 
	OnLeft     = NULL;
	OnRight    = NULL;
	OnUp       = NULL;
	OnDown     = NULL;
	Running    = false;
	PressedKey = 0;
	MonitoringON = false;
	MouseLBDown = false;
	FShow_GraphikPoint = { 0,0 };
	FAddedMonitoredObject = NULL;
	MainFormAnalisMapObj = true;

	DoAfterCreate();

	FAddForm = new CAddForm();
	FAddForm->FormCreate(this);
	FAddForm->FormLoadPeram(this);
	FAddForm->FormDraw(this);

	FAddForm->FDeviceTextBox1->OnTextInput = &TextInputBox_OnTextInput;
	FAddForm->FDeviceTextBox2->OnTextInput = &TextInputBox_OnTextInput;
	FAddForm->FDeviceTextBox3->OnTextInput = &TextInputBox_OnTextInput;
	FAddForm->FDeviceTextBox4->OnTextInput = &TextInputBox_OnTextInput;
	FAddForm->FDeviceTextBox5->OnTextInput = &TextInputBox_OnTextInput;
	FAddForm->FDeviceTextBox6->OnTextInput = &TextInputBox_OnTextInput;
	FAddForm->FOkButtonDevice->OnButtonClick = &OkButtonDevice_OnButtonClick;
	FAddForm->FOkButtonInterface->OnButtonClick = &OkButtonInterface_OnButtonClick;
	FAddForm->FOkButtonParametr->OnButtonClick = &OkButtonParametr_OnButtonClick;
	FAddForm->FCancelButton->OnButtonClick = &CancelButton_OnButtonClick;
	FAddForm->FOkButton->OnButtonClick = &OkButton_OnButtonClick;
}

void Application::Run() {
	Running = true;
	bool flag_mause_move = false;
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);
	DWORD numEvents = 0; // Количество непрочитанных сообщений
	DWORD numEventsRead = 0; // Количество прочитанных сообщений

	HWND hwnd = GetConsoleWindow();
	ShowCursor(FALSE);
	AllocConsole();
	const unsigned pressedMask = 1u << sizeof(SHORT) * 8;

	struct tm newtime;
	char am_pm[] = "AM";
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);
	printf("%d", newtime.tm_min);

	int min_prev = newtime.tm_min;

	int LDelay = 100;

	while (Running) {

		if (LDelay > 0) {
			LDelay--;
		}
		else {
			if (true == MonitoringON) {
				_time64(&long_time);
				err = _localtime64_s(&newtime, &long_time);

				if (min_prev != newtime.tm_min) {
					min_prev = newtime.tm_min;
					DoOnMonitoringButton();
					GraphikReDraw();
				}
			}
			LDelay = 100;
		}


		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents,
				&numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode ==
						VK_ESCAPE) {
						DoProcessKey(VK_ESCAPE);
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar ==
						'd')
					{
						// перерисовка по клавише 'd'
					}
				}
				if (eventBuffer[i].EventType == FOCUS_EVENT) {
					Sleep(300);
					Show(); // перерисовка при получении фокуса
				}
				
			}
			delete[] eventBuffer;
		}

/*		PressedKey = _getch();
		if ((0xE0 != PressedKey) && (0 != PressedKey)) {
			DoProcessKey(PressedKey);
		}
*/
		const unsigned stateLButton = static_cast<unsigned>(GetKeyState(VK_LBUTTON));
		int pos_for_draw;
		POINT mause_down = { 0,0 };
		if (pressedMask & stateLButton) // if pressed
		{
			if (true == flag_mause_move) {
				POINT cursorPos;
				hwnd = GetConsoleWindow();
				GetCursorPos(&cursorPos);
				ScreenToClient(hwnd, &cursorPos);
				pos_for_draw = (mause_down.x - MapObject[0]->FPosition.left) + (cursorPos.x - mause_down.x);

				BitBlt(Frame, MapObject[0]->FPosition.left, MapObject[0]->FPosition.top, (MapObject[0]->FPosition.right - MapObject[0]->FPosition.left),
					(MapObject[0]->FPosition.bottom - MapObject[0]->FPosition.top), GraphikHDC, FShow_GraphikPoint.x + pos_for_draw, 0, SRCCOPY);


			}
			else {
				POINT cursorPos;
				hwnd = GetConsoleWindow();
				GetCursorPos(&cursorPos);
				ScreenToClient(hwnd, &cursorPos);
				FindInPressedMap(cursorPos);
			}

		}
		const unsigned stateMButton1 = static_cast<unsigned>(GetKeyState(VK_MBUTTON));
		if (pressedMask & stateMButton1) // if pressed
		{
			if (pressedMask & stateLButton) {
				hwnd = GetConsoleWindow();
				GetCursorPos(&mause_down);
				ScreenToClient(hwnd, &mause_down);
				if (false == flag_mause_move) {
					flag_mause_move = true;
				}
				else {
					flag_mause_move = false;
					FShow_GraphikPoint.x += pos_for_draw;
				}
				Sleep(500);
			}

		}
		Sleep(30);
		Show();
	}

/*	while (Running) {
		PressedKey = _getch();
		if ( (0xE0!= PressedKey) && (0 != PressedKey) ) {
			DoProcessKey(PressedKey);
		}
		Show();
	}
*/
}

void Application::DoProcessKey(const int AKeyPressed) {
	switch (AKeyPressed) {
	    case Console::keyEscape: { DoOnKeyEscape(); break; }
		case Console::keyLeft  : { DoOnKeyLeft  (); break; }
		case Console::keyRight : { DoOnKeyRight (); break; }
		case Console::keyUp    : { DoOnKeyUp    (); break; }
		case Console::keyDown  : { DoOnKeyDown  (); break; }
		case Console::keyF1    : { DoOnKeyF1(); break; }
		case Console::keyF2    : { DoOnKeyF2(); break; }
		case Console::keyF3    : { DoOnKeyF3(); break; }
		case Console::keyF4    : { DoOnKeyF4(); break; }
		case Console::keyF5    : { DoOnKeyF5(); break; }
		case Console::keyF6    : { DoOnKeyF6(); break; }
		case Console::keyF7    : { DoOnKeyF7(); break; }
		case Console::keyF8    : { DoOnKeyF8(); break; }
		case Console::keyF9    : { DoOnKeyF9(); break; }
		case Console::keyF10   : { DoOnKeyF10(); break; }
		case Console::keyF11   : { DoOnKeyF11(); break; }
		case Console::keyF12   : { DoOnKeyF12(); break; }
	    // для выяснения нажатой клавиши, из реального проекта - исключить!!!
		/*
		default: {
			printf("pressed key \"%d\" \n", APressedKey);
			break;
		}
		*/
	}
}

void Application::DoOnKeyEscape() { if (NULL != OnEscape) OnEscape(this); }
void Application::DoOnKeyLeft()   { if (NULL != OnLeft  ) OnLeft  (this); }
void Application::DoOnKeyRight()  { if (NULL != OnRight ) OnRight (this); }
void Application::DoOnKeyUp()     { if (NULL != OnUp    ) OnUp    (this); }
void Application::DoOnKeyDown()   { if (NULL != OnDown  ) OnDown  (this); }
void Application::DoOnKeyF1()     { if (NULL != OnF1    ) OnF1    (this); }
void Application::DoOnKeyF2()     { if (NULL != OnF2    ) OnF2    (this); }
void Application::DoOnKeyF3()     { if (NULL != OnF3    ) OnF3    (this); }
void Application::DoOnKeyF4()     { if (NULL != OnF4    ) OnF4    (this); }
void Application::DoOnKeyF5()     { if (NULL != OnF5    ) OnF5    (this); }
void Application::DoOnKeyF6()     { if (NULL != OnF6    ) OnF6    (this); }
void Application::DoOnKeyF7()     { if (NULL != OnF7    ) OnF7    (this); }
void Application::DoOnKeyF8()     { if (NULL != OnF8    ) OnF8    (this); }
void Application::DoOnKeyF9()     { if (NULL != OnF9    ) OnF9    (this); }
void Application::DoOnKeyF10()    { if (NULL != OnF10   ) OnF10   (this); }
void Application::DoOnKeyF11()    { if (NULL != OnF11   ) OnF11   (this); }
void Application::DoOnKeyF12()    { if (NULL != OnF12   ) OnF12   (this); }

void Application::DoOnMonitoringButton() {
	for (CMonitoredParam* LMonitoredParam : MonitoredObj[0]->FMonitoredInstance[0]->FMonitoredParam) {


		// сформировать батник
		char* LName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LName, StringHelper::DefaultBufferSize);

		FILE* MyFile;
		char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
		strcpy_s(FileName, StringHelper::DefaultBufferSize, "temp.bat");

		int FileOpenError = fopen_s(&MyFile, FileName, "w+");
		if (0 == FileOpenError) {
			fprintf(MyFile, "%s", "@echo off\n");
			fprintf(MyFile, "%s", "date /T > d:\\log\n");
			fprintf(MyFile, "%s", "time /t >> d:\\log\n");
			fprintf(MyFile, "%s", LMonitoredParam->FSNMPComand);
			fclose(MyFile);
		}

		// запустить батник
		system("temp.bat");
		this->Show();

		// распарсить результат батника
		int flag = 0;
		StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
		strcpy_s(FileName, StringHelper::DefaultBufferSize, "d:\\log");

		char* LData = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LData, StringHelper::DefaultBufferSize);
		char* LTime = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LTime, StringHelper::DefaultBufferSize);
		char* LValue = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LValue, StringHelper::DefaultBufferSize);
		char* Buffer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);


		FileOpenError = fopen_s(&MyFile, FileName, "r");
		if (0 == FileOpenError) {

			char* parser = NULL;
			int flag = 0;

			char* Work = Buffer;
			while (!feof(MyFile)) {
				*Work = fgetc(MyFile);
				if (*Work != '\n') {
					Work++;
				}
				else {
					parser = Buffer;
					if (0 == flag) {
						parser = StringHelper::Parse(parser, '\n', LData, StringHelper::DefaultBufferSize);
						flag++;
					}
					else if (1 == flag) {
						parser = StringHelper::Parse(parser, '\n', LTime, StringHelper::DefaultBufferSize);
						flag++;
					}
					else {
						while (NULL != strstr(parser, ":")) {
							parser = strstr(parser, ":");
							parser++;
						}
						parser = StringHelper::Parse(parser, '\n', LValue, StringHelper::DefaultBufferSize);
					}
					StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
					Work = Buffer;
				}

				// добавить значение в массив значений

			}
			LMonitoredParam->AddCValues(LData, LTime, atoi(LValue));
			LMonitoredParam->CountDelta(LMonitoredParam->FValues.size()-2);
			fclose(MyFile);
		}
		// дописать полученніе значения в лог файл

		StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
		strcpy_s(FileName, StringHelper::DefaultBufferSize, LMonitoredParam->FLogfileName);

		FileOpenError = fopen_s(&MyFile, FileName, "a+");
		if (0 == FileOpenError) {
			fprintf(MyFile, "%s|%s|%s\n", LData, LTime, LValue);
			fclose(MyFile);
		}

		free(FileName);
		free(LData);
		free(LTime);
		free(LValue);
		free(Buffer);
	}
}


void Application::LoadGraficRes(char* aFileName) {

	FILE* MyFile;
	MyColor* BitmapColorArray1 = NULL;
	MyColor* Temp_BitmapColorArray1 = NULL;

	MyColor* BitmapColorArray2 = NULL;
	MyColor* Temp_BitmapColorArray2 = NULL;

	MyColor* BitmapColorArray3 = NULL;
	MyColor* Temp_BitmapColorArray3 = NULL;

	int LHeight_int = 0;
	int LWidth_int = 0;

	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "InputHost.bat");


	int FileOpenError = fopen_s(&MyFile, aFileName, "r");
	if (0 == FileOpenError) {
		char* Buffer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);

		char* LHeight = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LHeight, StringHelper::DefaultBufferSize);
		char* LWidth = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LWidth, StringHelper::DefaultBufferSize);
		char* LA = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LA, StringHelper::DefaultBufferSize);
		char* LR1 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LR1, StringHelper::DefaultBufferSize);
		char* LG1 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LG1, StringHelper::DefaultBufferSize);
		char* LB1 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LB1, StringHelper::DefaultBufferSize);

		char* LR2 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LR2, StringHelper::DefaultBufferSize);
		char* LG2 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LG2, StringHelper::DefaultBufferSize);
		char* LB2 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LB2, StringHelper::DefaultBufferSize);

		char* LR3 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LR3, StringHelper::DefaultBufferSize);
		char* LG3 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LG3, StringHelper::DefaultBufferSize);
		char* LB3 = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LB3, StringHelper::DefaultBufferSize);


		char* parser = NULL;
		int flag = 0;

		char* Work = Buffer;
		while (!feof(MyFile)) {
			*Work = fgetc(MyFile);
			if (*Work != '\n') {
				Work++;
			}
			else {

				if (0 == flag) {
					parser = Buffer;
					parser = StringHelper::Parse(parser, ' ', LHeight, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '\n', LWidth, StringHelper::DefaultBufferSize);
					LHeight_int = atoi(LHeight);
					LWidth_int = atoi(LWidth);
					BitmapColorArray1 = (MyColor*)malloc(LHeight_int * LWidth_int * sizeof(MyColor));
					Temp_BitmapColorArray1 = BitmapColorArray1;
					BitmapColorArray2 = (MyColor*)malloc(LHeight_int * LWidth_int * sizeof(MyColor));
					Temp_BitmapColorArray2 = BitmapColorArray2;
					BitmapColorArray3 = (MyColor*)malloc(LHeight_int * LWidth_int * sizeof(MyColor));
					Temp_BitmapColorArray3 = BitmapColorArray3;
					flag++;
					StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
					Work = Buffer;
				}
				else {
					parser = Buffer;
					//					parser = StringHelper::Parse(parser, ' ', LA, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LR1, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LG1, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LB1, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LR2, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LG2, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LB2, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LR3, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LG3, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '\n', LB3, StringHelper::DefaultBufferSize);
					//					Temp_BitmapColorArray->A = atoi(LA);
					Temp_BitmapColorArray1->R = atoi(LR1);
					Temp_BitmapColorArray1->G = atoi(LG1);
					Temp_BitmapColorArray1->B = atoi(LB1);
					Temp_BitmapColorArray1++;
					Temp_BitmapColorArray2->R = atoi(LR2);
					Temp_BitmapColorArray2->G = atoi(LG2);
					Temp_BitmapColorArray2->B = atoi(LB2);
					Temp_BitmapColorArray2++;
					Temp_BitmapColorArray3->R = atoi(LR3);
					Temp_BitmapColorArray3->G = atoi(LG3);
					Temp_BitmapColorArray3->B = atoi(LB3);
					Temp_BitmapColorArray3++;
					StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
					Work = Buffer;
				}

			}

		}

		free(Buffer);
		free(LHeight);
		free(LWidth);
		free(LA);
		free(LR1);
		free(LG1);
		free(LB1);
		free(LR2);
		free(LG2);
		free(LB2);
		free(LR3);
		free(LG3);
		free(LB3);

		fclose(MyFile);
	}
	else {
		printf("Не удалось открыть файл!\n");
	}
	free(FileName);

/*	HDC Lhdc = GetDC(GetConsoleWindow());
	Temp_BitmapColorArray = BitmapColorArray;
	for (int i = 0; i < LHeight_int; i++) {
		for (int j = 0; j < LWidth_int; j++) {
			SetPixel(Lhdc, i, j, RGB(Temp_BitmapColorArray->R, Temp_BitmapColorArray->G, Temp_BitmapColorArray->B));
			Temp_BitmapColorArray++;
		}
	}
*/
	Temp_BitmapColorArray1 = BitmapColorArray1;
	Temp_BitmapColorArray2 = BitmapColorArray2;
	Temp_BitmapColorArray3 = BitmapColorArray3;
	for (int i = 0; i < LHeight_int; i++) {
		for (int j = 0; j < LWidth_int; j++) {
			SetPixel(Mainform, i, j, RGB(Temp_BitmapColorArray1->R, Temp_BitmapColorArray1->G, Temp_BitmapColorArray1->B));
			Temp_BitmapColorArray1++;
			SetPixel(MainformNotPressed, i, j, RGB(Temp_BitmapColorArray2->R, Temp_BitmapColorArray2->G, Temp_BitmapColorArray2->B));
			Temp_BitmapColorArray2++;
			SetPixel(MainformPressed, i, j, RGB(Temp_BitmapColorArray3->R, Temp_BitmapColorArray3->G, Temp_BitmapColorArray3->B));
			Temp_BitmapColorArray3++;
		}
	}


}


void Application::Show() {
	HDC Lhdc = GetDC(GetConsoleWindow());
	BitBlt(Lhdc, 0, 0, 1700, 1000, Frame, 0, 0, SRCCOPY);
	ReleaseDC(GetConsoleWindow(), Lhdc);
}



void Application::DoAfterCreate() {
	// Формирование буфера с графическим ресурсом

	HDC localdc = GetDC(GetConsoleWindow());

	Mainform = CreateCompatibleDC(localdc);
	MainFormBitmap = CreateCompatibleBitmap(localdc, 1300, 900);
	SelectObject(Mainform, MainFormBitmap);

	MainformPressed = CreateCompatibleDC(localdc);
	MainFormPressedBitmap = CreateCompatibleBitmap(localdc, 1300, 900);
	SelectObject(MainformPressed, MainFormPressedBitmap);

	MainformNotPressed = CreateCompatibleDC(localdc);
	MainFormNotPressedBitmap = CreateCompatibleBitmap(localdc, 1300, 900);
	SelectObject(MainformNotPressed, MainFormNotPressedBitmap);

	GraphikHDC = CreateCompatibleDC(localdc);
	GraphikBitmap = CreateCompatibleBitmap(localdc, 2000, 300);
	SelectObject(GraphikHDC, GraphikBitmap);

	Frame = CreateCompatibleDC(localdc);
	FrameBitmap = CreateCompatibleBitmap(localdc, 1700, 1000);
	SelectObject(Frame, FrameBitmap);

	char* LFileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(LFileName, StringHelper::DefaultBufferSize);
	strcpy_s(LFileName, StringHelper::DefaultBufferSize, "MainForm.txt");

	LoadGraficRes(LFileName);
	free(LFileName);

	CreateStartFrame();

	Show();

	LoadConfMonitoredObj();
	for (CMonitoredObject* LMonitoredObject : MonitoredObj) {
		for (CPort* LPort : LMonitoredObject->FMonitoredInstance) {
			for (CMonitoredParam* LMonitoredParam : LPort->FMonitoredParam) {
				LMonitoredParam->LoadValues();
				LMonitoredParam->CountDelta();
			}
		}
	}

	LoadMapObj();
//	for (int i = 0; i < 3; i++) {
//		AddMonitoredObj();
//	}


}


void Application::FindInPressedMap(POINT aCursorPos) {
	char* LName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(LName, StringHelper::DefaultBufferSize);
	int findflag = 0;
	CMapObjectItem* WorkMapObjectItem = NULL;

	RECT LTemp_Point_AddForm;

	for (CMapObjectItem* LMapObjectItem : MapObject) {

		if ((true == FAddForm->FVisible) && (0 == strcmp(LMapObjectItem->FConteiner_Name, FAddForm->FName))) {
			LTemp_Point_AddForm.left = FAddForm->FPosition.left + LMapObjectItem->FPosition.left;
			LTemp_Point_AddForm.right = FAddForm->FPosition.left + LMapObjectItem->FPosition.right;
			LTemp_Point_AddForm.top = FAddForm->FPosition.top + LMapObjectItem->FPosition.top;
			LTemp_Point_AddForm.bottom = FAddForm->FPosition.top + LMapObjectItem->FPosition.bottom;
			if (Console::InRect(LTemp_Point_AddForm, aCursorPos)) {
				WorkMapObjectItem = LMapObjectItem;
				findflag = 1;
				break;
			}
		}
		else if ((true == MainFormAnalisMapObj) && (0 == strcmp(LMapObjectItem->FConteiner_Name, "MainForm"))) {
			if (Console::InRect(LMapObjectItem->FPosition, aCursorPos)) {
				WorkMapObjectItem = LMapObjectItem;
				findflag = 1;
				break;
			}
		}
	}

	if (1 == findflag) {

		if (0 == strcmp(WorkMapObjectItem->FConteiner_Name, FAddForm->FName)) {
			if (0 == strcmp(WorkMapObjectItem->FName, "DeviceTextBox1")) {
				FAddForm->FDeviceTextBox1->DoOnTextInput(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "DeviceTextBox2")) {
				FAddForm->FDeviceTextBox2->DoOnTextInput(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "DeviceTextBox3")) {
				FAddForm->FDeviceTextBox3->DoOnTextInput(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "DeviceTextBox4")) {
				FAddForm->FDeviceTextBox4->DoOnTextInput(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "DeviceTextBox5")) {
				FAddForm->FDeviceTextBox5->DoOnTextInput(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "DeviceTextBox6")) {
				FAddForm->FDeviceTextBox6->DoOnTextInput(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "OkButtonDevice")) {
				FAddForm->FOkButtonDevice->DoOnButtonClick(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
				Show();
				Sleep(300);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "OkButtonInterface")) {
				FAddForm->FOkButtonInterface->DoOnButtonClick(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
				Show();
				Sleep(300);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "OkButtonParametr")) {
				FAddForm->FOkButtonParametr->DoOnButtonClick(this);
				FAddForm->FormDraw(this);
				FAddForm->FormShow(Frame);
				Show();
				Sleep(300);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "CancelButton")) {
				FAddForm->FCancelButton->DoOnButtonClick(this);
				CreateStartFrame();
				for (CMapObjectItem* LTempMapObjectItem : MapObject) {
					if (0 == strcmp(LTempMapObjectItem->FName, "MonitoringButton")) {
						ReDrawMonitoringButton(LTempMapObjectItem);
						break;
					}
				}
				Show();
				Sleep(300);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "OkButton")) {
				FAddForm->FOkButton->DoOnButtonClick(this);
				CreateStartFrame();
				for (CMapObjectItem* LTempMapObjectItem : MapObject) {
					if (0 == strcmp(LTempMapObjectItem->FName, "MonitoringButton")) {
						ReDrawMonitoringButton(LTempMapObjectItem);
						break;
					}
				}
				Show();
				Sleep(300);
			}
		}
		else if (0 == strcmp(WorkMapObjectItem->FConteiner_Name, "MainForm")) {
			if (0 == strcmp(WorkMapObjectItem->FName, "GraphikArea")) {
				DoGraphikAreaClick(WorkMapObjectItem);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "ExitButton")) {
//				SaveConfMonitoredObjAll();
				DoOnKeyEscape();
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "MonitoringButton")) {
				DoMonitoringButtonClick(WorkMapObjectItem);
			}
			if (0 == strcmp(WorkMapObjectItem->FName, "AddButton")) {
				DoAddButtonClick(WorkMapObjectItem);
			}
		}

	}


}

void Application::AddMonitoredObj() {
	CMonitoredObject* LMonitoredObj = new CMonitoredObject();
	strcpy_s(LMonitoredObj->FName, StringHelper::DefaultBufferSize, "LocalHost");
	strcpy_s(LMonitoredObj->FIpAdress, StringHelper::DefaultBufferSize, "localhost");
	strcpy_s(LMonitoredObj->FVersionSNMP, StringHelper::DefaultBufferSize, "2c");
	strcpy_s(LMonitoredObj->FConectionString, StringHelper::DefaultBufferSize, "public");

	MonitoredObj.push_back(LMonitoredObj);
}

void Application::AddMonitoredObj(char* aName, char* aIpAdress, char* aVersionSNMP, char* aConectionString) {
	CMonitoredObject* LMonitoredObj = new CMonitoredObject();
	strcpy_s(LMonitoredObj->FName, StringHelper::DefaultBufferSize, aName);
	strcpy_s(LMonitoredObj->FIpAdress, StringHelper::DefaultBufferSize, aIpAdress);
	strcpy_s(LMonitoredObj->FVersionSNMP, StringHelper::DefaultBufferSize, aVersionSNMP);
	strcpy_s(LMonitoredObj->FConectionString, StringHelper::DefaultBufferSize, aConectionString);

	MonitoredObj.push_back(LMonitoredObj);
}

void Application::SaveConfMonitoredObj(CMonitoredObject* aMonObj) {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "MonitoredObjectLog.txt");

	int FileOpenError = fopen_s(&MyFile, FileName, "a+");
	if (0 == FileOpenError) {
		fprintf(MyFile, "1|%s|%s|%s|%s\n", aMonObj->FName, aMonObj->FIpAdress, aMonObj->FVersionSNMP, aMonObj->FConectionString);
		fclose(MyFile);
	}
	free(FileName);
}

Application::~Application() {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "MonitoredObjectLog.txt");

	int FileOpenError = fopen_s(&MyFile, FileName, "w+");
	if (0 == FileOpenError) {
		fclose(MyFile);
	}
	free(FileName);

	SaveConfMonitoredObjAll();

	for (CMonitoredObject* LMonObj : MonitoredObj) {
//		SaveConfMonitoredObj(LMonObj);
		delete(LMonObj);
	}
}

void Application::SaveConfMonitoredObjAll() {
	for (CMonitoredObject* LMonObj : MonitoredObj) {

		SaveConfMonitoredObj(LMonObj);
		for (CPort* LPort : LMonObj->FMonitoredInstance) {
			LMonObj->SaveConfMonitoredInstance(LPort);
			for (CMonitoredParam* LMonitoredParam : LPort->FMonitoredParam) {
				LPort->SaveMonitoredParam(LMonitoredParam);
			}
		}
	}
}


void Application::LoadConfMonitoredObj() {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "MonitoredObjectLog.txt");

	int LTypeObj_int = -1;
	int FileOpenError = fopen_s(&MyFile, FileName, "r");
	if (0 == FileOpenError) {
		char* Buffer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);

		char* LTypeObj = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LTypeObj, StringHelper::DefaultBufferSize);
		char* LName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LName, StringHelper::DefaultBufferSize);
		char* LIpAdress = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LIpAdress, StringHelper::DefaultBufferSize);
		char* LVersionSNMP = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LVersionSNMP, StringHelper::DefaultBufferSize);
		char* LConectionString = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LConectionString, StringHelper::DefaultBufferSize);
		char* LLogFileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LLogFileName, StringHelper::DefaultBufferSize);

		int LIndexMonitoredObj = -1;
		int LIndexPorts = -1;
		char* parser = NULL;
		int flag = 0;

		char* Work = Buffer;
		while (!feof(MyFile)) {
			*Work = fgetc(MyFile);
			if (*Work != '\n') {
				Work++;
			}
			else {
				parser = Buffer;
				//					parser = StringHelper::Parse(parser, ' ', LA, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LTypeObj, StringHelper::DefaultBufferSize);

				LTypeObj_int = atoi(LTypeObj);
				switch (LTypeObj_int) {
				case	1: 
					parser = StringHelper::Parse(parser, '|', LName, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '|', LIpAdress, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '|', LVersionSNMP, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '\n', LConectionString, StringHelper::DefaultBufferSize);
					AddMonitoredObj(LName, LIpAdress, LVersionSNMP, LConectionString);
					LIndexMonitoredObj++;
					LIndexPorts = -1;
					break;
				
				case	2:
					parser = StringHelper::Parse(parser, '\n', LName, StringHelper::DefaultBufferSize);
					MonitoredObj[LIndexMonitoredObj]->AddMonitoredInstance(LName);
					LIndexPorts++;
					break;
				case	3:
					parser = StringHelper::Parse(parser, '|', LName, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '|', LConectionString, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '\n', LLogFileName, StringHelper::DefaultBufferSize);
					MonitoredObj[LIndexMonitoredObj]->FMonitoredInstance[LIndexPorts]->AddMonitoredParam(LName, LConectionString, LLogFileName);
					break;
			}

				StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
				StringHelper::Null(LTypeObj, StringHelper::DefaultBufferSize);
				StringHelper::Null(LName, StringHelper::DefaultBufferSize);
				StringHelper::Null(LIpAdress, StringHelper::DefaultBufferSize);
				StringHelper::Null(LVersionSNMP, StringHelper::DefaultBufferSize);
				StringHelper::Null(LConectionString, StringHelper::DefaultBufferSize);
				StringHelper::Null(LLogFileName, StringHelper::DefaultBufferSize);
				Work = Buffer;
			}
		}
		free(Buffer);
		free(LName);
		free(LIpAdress);
		free(LVersionSNMP);
		free(LConectionString);
		free(LLogFileName);

		fclose(MyFile);
	}
	free(FileName);

}


void Application::DoMonitoringButtonClick(CMapObjectItem* Sender) {
		MonitoringON = !MonitoringON;
		Sender->FPressed = !Sender->FPressed;
		ReDrawMonitoringButton(Sender);
		Show();
		Sleep(500);
		
//	if (true == MonitoringON) {
//		DoOnMonitoringButton();
//	}
}

void Application::DoAddButtonClick(CMapObjectItem* Sender) {
	Sender->FPressed = !Sender->FPressed;
	MainFormAnalisMapObj = false;
	ReDrawAddButton(Sender);
	FAddForm->FVisible = true;
	FAddForm->FormDraw(this);
	FAddForm->FormShow(Frame);
	Show();
	Sleep(100);
}


void Application::ReDrawMonitoringButton(CMapObjectItem* Sender) {
	if (false == Sender->FPressed) {
		BitBlt(Frame, Sender->FPosition.left, Sender->FPosition.top, Sender->FPosition.right - Sender->FPosition.left, Sender->FPosition.bottom - Sender->FPosition.top,
			   MainformNotPressed, Sender->FPosition.left, Sender->FPosition.top, SRCCOPY);
	}
	else {
		BitBlt(Frame, Sender->FPosition.left, Sender->FPosition.top, Sender->FPosition.right - Sender->FPosition.left, Sender->FPosition.bottom - Sender->FPosition.top,
			MainformPressed, Sender->FPosition.left, Sender->FPosition.top, SRCCOPY);
	}

}

void Application::ReDrawAddButton(CMapObjectItem* Sender) {
	if (false == Sender->FPressed) {
		BitBlt(Frame, Sender->FPosition.left, Sender->FPosition.top, Sender->FPosition.right - Sender->FPosition.left, Sender->FPosition.bottom - Sender->FPosition.top,
			MainformNotPressed, Sender->FPosition.left, Sender->FPosition.top, SRCCOPY);
	}
	else {
		BitBlt(Frame, Sender->FPosition.left, Sender->FPosition.top, Sender->FPosition.right - Sender->FPosition.left, Sender->FPosition.bottom - Sender->FPosition.top,
			MainformPressed, Sender->FPosition.left, Sender->FPosition.top, SRCCOPY);
}

}


void Application::GraphikPaint(CMonitoredParam* aMonitoredParam, CMapObjectItem* aMapObjectItem) {
	CMonitoredParam* LMonitoredParam = aMonitoredParam;

//	CMonitoredParam* LMonitoredParam = MonitoredObj[0]->FMonitoredInstance[0]->FMonitoredParam[0];

//	HDC localdc = GetDC(GetConsoleWindow());
//	GraphikHDC = CreateCompatibleDC(localdc);
//	GraphikBitmap = CreateCompatibleBitmap(localdc, 2000, 400);
//	SelectObject(GraphikHDC, GraphikBitmap);
	
	size_t LValuesSize;
	LValuesSize = LMonitoredParam->FValues.size() - 1;
	HBRUSH hBrush1; 
	hBrush1 = CreateSolidBrush(RGB(215, 120, 140)); 

	HBRUSH Lold_brush;
	RECT DrawRect;
	DrawRect = { 0,0,2000,(aMapObjectItem->FPosition.bottom - aMapObjectItem->FPosition.top) };
	HBRUSH hBrush2 = CreateSolidBrush(RGB(184, 213, 231));
	Lold_brush = (HBRUSH)SelectObject(GraphikHDC, hBrush2);
	FillRect(GraphikHDC, &DrawRect, hBrush2);
	SelectObject(GraphikHDC, Lold_brush);
	DeleteObject(SelectObject(GraphikHDC, hBrush2));

	Lold_brush = (HBRUSH)SelectObject(GraphikHDC, hBrush1);

	int Output_Value = 0;
	double Max_delta = 0.;
	for (int Values_Pos = LValuesSize; Values_Pos > 0; Values_Pos--) {
		if (LMonitoredParam->FValues[Values_Pos]->FDelta > Max_delta) {
			Max_delta = LMonitoredParam->FValues[Values_Pos]->FDelta;
		}
	}

	double LCoef_output = Max_delta*1.2 / ((aMapObjectItem->FPosition.bottom - aMapObjectItem->FPosition.top)*0.8);

	COORD Output_Cursor_Pos = {0,(int)((double)(aMapObjectItem ->FPosition.bottom- aMapObjectItem->FPosition.top)*0.8)};
	for (int Values_Pos = LValuesSize; Values_Pos > 0; Values_Pos--) {
//		Output_Value = LMonitoredParam->FValues[Values_Pos]->FValue - LMonitoredParam->FValues[Values_Pos - 1]->FValue;
		
//		Rectangle(GraphikHDC, Output_Cursor_Pos.X, Output_Cursor_Pos.Y, Output_Cursor_Pos.X + 20, Output_Cursor_Pos.Y - Output_Value / 20000);
		DrawRect.left = 50 + Output_Cursor_Pos.X;
		DrawRect.right = 50 + Output_Cursor_Pos.X + 10;
		DrawRect.top = Output_Cursor_Pos.Y - LMonitoredParam->FValues[Values_Pos]->FDelta / LCoef_output;
		DrawRect.bottom = Output_Cursor_Pos.Y;
		FillRect(GraphikHDC, &DrawRect, hBrush1);
		Output_Cursor_Pos.X += 10;
	}

	SelectObject(GraphikHDC, Lold_brush);
	DeleteObject(SelectObject(GraphikHDC, hBrush1));
}

void Application::GraphikShow(CMapObjectItem* aMapObjectItem) {
	HDC Lhdc = GetDC(GetConsoleWindow());
	BitBlt(Frame, aMapObjectItem->FPosition.left, aMapObjectItem->FPosition.top, (aMapObjectItem->FPosition.right-aMapObjectItem->FPosition.left),
		        (aMapObjectItem->FPosition.bottom- aMapObjectItem->FPosition.top), GraphikHDC, 0, 0, SRCCOPY);
}

void Application::DoGraphikAreaClick(CMapObjectItem* aMapObjectItem) {
	GraphikPaint(MonitoredObj[0]->FMonitoredInstance[0]->FMonitoredParam[1], aMapObjectItem);
	GraphikShow(aMapObjectItem);
}


void Application::AddMapObjItem(char* aName, int aLeft, int aTop, int aright, int aBottom, int aWidth, int aHeight, char* aCaption, char*  aConteiner_Name) {
	CMapObjectItem* LMapObjectItem = new CMapObjectItem();
	strcpy_s(LMapObjectItem->FName, StringHelper::DefaultBufferSize, aName);
	LMapObjectItem->FPosition.left = aLeft;
	LMapObjectItem->FPosition.top = aTop;
	LMapObjectItem->FPosition.right = aright;
	LMapObjectItem->FPosition.bottom = aBottom;
	LMapObjectItem->FWidth = aWidth;
	LMapObjectItem->FHeight = aHeight;
	strcpy_s(LMapObjectItem->FCaption, StringHelper::DefaultBufferSize, aCaption);
	strcpy_s(LMapObjectItem->FConteiner_Name, StringHelper::DefaultBufferSize, aConteiner_Name);
	MapObject.push_back(LMapObjectItem);
}


void Application::LoadMapObj() {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "MapObjects.txt");

	int FileOpenError = fopen_s(&MyFile, FileName, "r");
	if (0 == FileOpenError) {
		char* Buffer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);

		char* LConteiner_Name = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LConteiner_Name, StringHelper::DefaultBufferSize);
		char* LName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LName, StringHelper::DefaultBufferSize);
		char* LCaption = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LCaption, StringHelper::DefaultBufferSize);
		char* LTop = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LTop, StringHelper::DefaultBufferSize);
		char* LBottom = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LBottom, StringHelper::DefaultBufferSize);
		char* LLeft = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LLeft, StringHelper::DefaultBufferSize);
		char* LRight = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LRight, StringHelper::DefaultBufferSize);
		char* LWidth = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LWidth, StringHelper::DefaultBufferSize);
		char* LHeight = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LHeight, StringHelper::DefaultBufferSize);

		char* parser = NULL;
		int flag = 0;

		char* Work = Buffer;
		while (!feof(MyFile)) {
			*Work = fgetc(MyFile);
			if (*Work != '\n') {
				Work++;
			}
			else {
				parser = Buffer;
				//					parser = StringHelper::Parse(parser, ' ', LA, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LConteiner_Name, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LName, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LLeft, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LTop, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LRight, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LBottom, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LWidth, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LHeight, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '\n', LCaption, StringHelper::DefaultBufferSize);

				StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
				Work = Buffer;
				AddMapObjItem(LName, atoi(LLeft), atoi(LTop), atoi(LRight), atoi(LBottom), atoi(LWidth), atoi(LHeight), LCaption, LConteiner_Name);
				StringHelper::Null(LName, StringHelper::DefaultBufferSize);
				StringHelper::Null(LLeft, StringHelper::DefaultBufferSize);
				StringHelper::Null(LTop, StringHelper::DefaultBufferSize);
				StringHelper::Null(LRight, StringHelper::DefaultBufferSize);
				StringHelper::Null(LBottom, StringHelper::DefaultBufferSize);
				StringHelper::Null(LWidth, StringHelper::DefaultBufferSize);
				StringHelper::Null(LHeight, StringHelper::DefaultBufferSize);
				StringHelper::Null(LCaption, StringHelper::DefaultBufferSize);

			}
		}
		free(Buffer);
		free(LName);
		free(LLeft);
		free(LTop);
		free(LRight);
		free(LBottom);
		free(LWidth);
		free(LHeight);
		free(LCaption);
		free(LConteiner_Name);

		free(FileName);

		fclose(MyFile);
	}

}


CMapObjectItem* Application::FindMapObject(char* aName) {
	CMapObjectItem* LResult = NULL;
	for (CMapObjectItem* LMapObjectItem : MapObject) {
		if (0==strcmp(LMapObjectItem->FName, aName)) {
			LResult= LMapObjectItem;
		}
	}
	return LResult;
}

void Application::GraphikReDraw() {
	char* LName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(LName, StringHelper::DefaultBufferSize);
	CMapObjectItem* LMapObjectItem;

	strcpy_s(LName, StringHelper::DefaultBufferSize, "GraphikArea");
	LMapObjectItem = FindMapObject(LName);
	if (NULL != LMapObjectItem) {
		GraphikPaint(MonitoredObj[0]->FMonitoredInstance[0]->FMonitoredParam[1], LMapObjectItem);
		GraphikShow(LMapObjectItem);
	}

	free(LName);
}

void Application::CreateStartFrame() {
	BitBlt(Frame, 0, 0, 1200, 800, Mainform, 0, 0, SRCCOPY);
	BitBlt(Frame, 0, 0, 1200, 85, MainformNotPressed, 0, 0, SRCCOPY);
	BitBlt(Frame, 0, 490, 1200, 57, MainformNotPressed, 0, 490, SRCCOPY);

}


void TextInputBox_OnTextInput(CTextInputBox* Sender, Application* App_Sender) {
	char* LBufer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(LBufer, StringHelper::DefaultBufferSize);
	char* LTemp_Bufer = LBufer;

	int i = 0;
	*LTemp_Bufer = _getch();
	while ((i < (StringHelper::DefaultBufferSize - 2)) && (*LTemp_Bufer != 13)) {
		LTemp_Bufer++;
		i++;
		strcpy_s(Sender->FCaaption, StringHelper::DefaultBufferSize, LBufer);
		App_Sender->FAddForm->FormDraw(App_Sender);
		App_Sender->FAddForm->FormShow(App_Sender->Frame);
		HDC Lhdc = GetDC(GetConsoleWindow());
		BitBlt(Lhdc, 0, 0, 1700, 1000, App_Sender->Frame, 0, 0, SRCCOPY);
		ReleaseDC(GetConsoleWindow(), Lhdc);

		*LTemp_Bufer = _getch();
	}
	*LTemp_Bufer = 0;

	strcpy_s(Sender->FCaaption, StringHelper::DefaultBufferSize, LBufer);
}

void OkButtonDevice_OnButtonClick(CButton* Sender, Application* App_Sender) {
	if (NULL == App_Sender->FAddedMonitoredObject) {
		App_Sender->FAddedMonitoredObject = new CMonitoredObject();
	}
	strcpy_s(App_Sender->FAddedMonitoredObject->FName, StringHelper::DefaultBufferSize, App_Sender->FAddForm->FDeviceTextBox1->FCaaption);
	strcpy_s(App_Sender->FAddedMonitoredObject->FIpAdress, StringHelper::DefaultBufferSize, App_Sender->FAddForm->FDeviceTextBox2->FCaaption);
	strcpy_s(App_Sender->FAddedMonitoredObject->FConectionString, StringHelper::DefaultBufferSize, App_Sender->FAddForm->FDeviceTextBox3->FCaaption);
	strcpy_s(App_Sender->FAddedMonitoredObject->FVersionSNMP, StringHelper::DefaultBufferSize, "2c");
	Sender->FPresseed = true;

	App_Sender->FAddForm->FOutputAreaTreeOutput->FormTextOut(App_Sender->FAddForm->Addform,App_Sender->FAddedMonitoredObject);

}

void OkButtonInterface_OnButtonClick(CButton* Sender, Application* App_Sender) {
	CPort* LPort = new CPort();
	strcpy_s(LPort->FName, StringHelper::DefaultBufferSize, App_Sender->FAddForm->FDeviceTextBox4->FCaaption);
	App_Sender->FAddedMonitoredObject->FMonitoredInstance.push_back(LPort);
	Sender->FPresseed = true;
	App_Sender->FAddForm->FOutputAreaTreeOutput->FormTextOut(App_Sender->FAddForm->Addform, App_Sender->FAddedMonitoredObject);

}

void OkButtonParametr_OnButtonClick(CButton* Sender, Application* App_Sender) {
	if (App_Sender->FAddedMonitoredObject->FMonitoredInstance.size() > 0) {
		char* LSNMPComand = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LSNMPComand, StringHelper::DefaultBufferSize);

		CMonitoredParam* LMonitoredParam = new CMonitoredParam();
		strcpy_s(LMonitoredParam->FName, StringHelper::DefaultBufferSize, App_Sender->FAddForm->FDeviceTextBox5->FCaaption);

		int LPos = App_Sender->FAddedMonitoredObject->FMonitoredInstance.size() - 1;
		strcpy_s(LSNMPComand, StringHelper::DefaultBufferSize, "c:\\usr\\bin\\snmpget -v 2c -c ");
		strcat_s(LSNMPComand, StringHelper::DefaultBufferSize, App_Sender->FAddedMonitoredObject->FConectionString);
		strcat_s(LSNMPComand, StringHelper::DefaultBufferSize, " ");
		strcat_s(LSNMPComand, StringHelper::DefaultBufferSize, App_Sender->FAddedMonitoredObject->FIpAdress);
		strcat_s(LSNMPComand, StringHelper::DefaultBufferSize, " ");
		strcat_s(LSNMPComand, StringHelper::DefaultBufferSize, App_Sender->FAddForm->FDeviceTextBox6->FCaaption);
		strcat_s(LSNMPComand, StringHelper::DefaultBufferSize, " >> d:\\log");

		strcpy_s(LMonitoredParam->FSNMPComand, StringHelper::DefaultBufferSize, LSNMPComand);

		char* LLogFile = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LLogFile, StringHelper::DefaultBufferSize);
		strcpy_s(LLogFile, StringHelper::DefaultBufferSize, App_Sender->FAddedMonitoredObject->FName);
		strcat_s(LLogFile, StringHelper::DefaultBufferSize, "_");
		strcat_s(LLogFile, StringHelper::DefaultBufferSize, App_Sender->FAddedMonitoredObject->FMonitoredInstance[LPos]->FName);
		strcat_s(LLogFile, StringHelper::DefaultBufferSize, "_");
		strcat_s(LLogFile, StringHelper::DefaultBufferSize, LMonitoredParam->FName);
		strcat_s(LLogFile, StringHelper::DefaultBufferSize, "_log.txt");

		strcpy_s(LMonitoredParam->FLogfileName, StringHelper::DefaultBufferSize, LLogFile);
		free(LSNMPComand);
		free(LLogFile);

		App_Sender->FAddedMonitoredObject->FMonitoredInstance[LPos]->FMonitoredParam.push_back(LMonitoredParam);
	}

}

void CancelButton_OnButtonClick(CButton* Sender, Application* App_Sender) {
	App_Sender->FAddForm->FVisible = false;
	App_Sender->MainFormAnalisMapObj = true;

	if (NULL != App_Sender->FAddedMonitoredObject) {
		delete(App_Sender->FAddedMonitoredObject);
		App_Sender->FAddedMonitoredObject = NULL;
	}
}


void OkButton_OnButtonClick(CButton* Sender, Application* App_Sender) {
	App_Sender->FAddForm->FVisible = false;
	App_Sender->MainFormAnalisMapObj = true;

	App_Sender->MonitoredObj.push_back(App_Sender->FAddedMonitoredObject);
	App_Sender->FAddedMonitoredObject = NULL;

}
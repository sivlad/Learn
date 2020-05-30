// SNMPAgent.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "../Application.h"
#include <vector>
#include <process.h>
#include <stdio.h>
#include "../StringHelper.h"
#include <conio.h>

void App_OnKeyEscape(Application* Sender) {
//	printf("pressed key Escape \n");
	Sender->Running = false;
}


//struct MyColor {
//	int A;
//	int R;
//	int G;
//	int B;
//};

int main() {

//	for (int i = 0; i < 1; i++) {
//		system("InputHost.bat");
//		Sleep(1000);
//	}


/*	FILE* MyFile;
	MyColor* BitmapColorArray = NULL;
	MyColor* Temp_BitmapColorArray = NULL;

	int LHeight_int = 0;
	int LWidth_int = 0;

	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "InputHost.bat");


	int FileOpenError = fopen_s(&MyFile, "MainForm.txt", "r");
	if (0 == FileOpenError) {
		char* Buffer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	    StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);

		char* LHeight = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LHeight, StringHelper::DefaultBufferSize);
		char* LWidth = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LWidth, StringHelper::DefaultBufferSize);
		char* LA = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LA, StringHelper::DefaultBufferSize);
		char* LR = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LR, StringHelper::DefaultBufferSize);
		char* LG = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LG, StringHelper::DefaultBufferSize);
		char* LB = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LB, StringHelper::DefaultBufferSize);

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
					BitmapColorArray = (MyColor*)malloc(LHeight_int * LWidth_int * sizeof(MyColor));
					flag++;
					Temp_BitmapColorArray = BitmapColorArray;
					StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
					Work = Buffer;
				}
				else {
					parser = Buffer;
//					parser = StringHelper::Parse(parser, ' ', LA, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LR, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, ' ', LG, StringHelper::DefaultBufferSize);
					parser = StringHelper::Parse(parser, '\n', LB, StringHelper::DefaultBufferSize);
//					Temp_BitmapColorArray->A = atoi(LA);
					Temp_BitmapColorArray->R = atoi(LR);
					Temp_BitmapColorArray->G = atoi(LG);
					Temp_BitmapColorArray->B = atoi(LB);
					Temp_BitmapColorArray++;
					StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
					Work = Buffer;
				}

			}

		}

		free(Buffer);
		free(LHeight);
		free(LWidth);
		free(LA);
		free(LR);
		free(LG);
		free(LB);

		fclose(MyFile);
	}
	else {
		printf("Не удалось открыть файл!\n");
		return 1;
	}
	free(FileName);

//	Temp_BitmapColorArray = BitmapColorArray;
//	for (int i = 0; i < 100; i++) {
//		printf("%d \t %d \t %d \t %d \n", Temp_BitmapColorArray->A, Temp_BitmapColorArray->R, Temp_BitmapColorArray->G, Temp_BitmapColorArray->B);
//		Temp_BitmapColorArray++;
//	}

	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	HDC hdc2 = CreateCompatibleDC(hdc);
	HBITMAP bitmap1 = CreateCompatibleBitmap(hdc, 2000, 2000);

	HDC hdc3 = CreateCompatibleDC(hdc);
	HBITMAP bitmap3 = CreateCompatibleBitmap(hdc, 2000, 2000);


	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hdc2, brush2);
	SelectObject(hdc2, bitmap1);
	SelectObject(hdc3, bitmap3);

	Temp_BitmapColorArray = BitmapColorArray;
	for (int i = 0; i < LHeight_int; i++) {
		for (int j = 0; j < LWidth_int; j++) {
			SetPixel(hdc2, i, j, RGB(Temp_BitmapColorArray->R, Temp_BitmapColorArray->G, Temp_BitmapColorArray->B));
			Temp_BitmapColorArray++;
		}
	}

	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	SelectObject(hdc, brush);
//	Rectangle(hdc2, 50, 50, 120, 120);
//	Rectangle(hdc, 0, 0, 100, 100);
	DeleteObject(brush);

	RECT SourthRect;
	RECT DestRect;
	SourthRect.left = 0;
	SourthRect.top = 0;
	SourthRect.right = LWidth_int;
	SourthRect.bottom = LHeight_int;
	DestRect.left = 0+100;
	DestRect.top = 0 + 100;
	DestRect.right = LWidth_int + 100;
	DestRect.bottom = LHeight_int + 100;


	brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc3, brush);

	const unsigned pressedMask = 1u << sizeof(SHORT) * 8;
	while (true)
	{
		const unsigned state = static_cast<unsigned>(GetKeyState(VK_LBUTTON));
//		const unsigned state1 = static_cast<unsigned>(GetKeyState(WM_LBUTTONUP));


		if (pressedMask & state) // if pressed
		{
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			ScreenToClient(hwnd, &cursorPos);

			Rectangle(hdc3, 0, 0, 2000, 2000);
			BitBlt(hdc3, cursorPos.x, cursorPos.y, cursorPos.x + LWidth_int, cursorPos.y + LHeight_int, hdc2, 0, 0, SRCCOPY);
			BitBlt(hdc, 0, 0, 2000, 2000, hdc3, 0, 0, SRCCOPY);

//			SetPixel(GetDC(hwnd), cursorPos.x, cursorPos.y, RGB(255, 255, 255));
//			Rectangle(GetDC(hwnd), cursorPos.x, cursorPos.y, cursorPos.x + 10, cursorPos.y + 10);
			// std::cout << cursorPos.x << ';' << cursorPos.y << std::endl;
		}

		Sleep(10);
	}


	DeleteObject(brush);


//	CopyRect(&SourthRect, &DestRect);
//	StretchBlt(hdc2, 0, 0, 400, 400, hdc, 0, 0, LWidth_int, LHeight_int, SRCCOPY);
	for (int i = 0; i < 100; i++) {
		brush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, brush);
		Rectangle(hdc, 0, 0, 1000, 1000);
		BitBlt(hdc, 0+i, 0+i, LWidth_int+i, LHeight_int+i, hdc2, 0, 0, SRCCOPY);
//		Sleep(400);
	}
//	BitBlt(hdc, 0, 0, LWidth_int, LHeight_int, hdc2, 0, 0, SRCCOPY);


//	Sleep(100000);
//	system("Pause");
	_getch();


*/
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Application* App = new Application();
	App->OnEscape = &App_OnKeyEscape;
	App->Run();
	delete App;
	return 0;
}

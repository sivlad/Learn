#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include "../ApplicationConsts.h"
#include "../ApplicationGlobals.h"
#include "../StringHelper.h"
#include "../Console.h"
#include "../Environment.h"
#include "../Directory.h"
#include "../Path.h"
#include "../TGeoObj.h"
#include "../TGeoObjBank.h"
#include "../TGeoObjHouse.h"
#include "../TGeoObjShop.h"
#include "../TGeoObjTank.h"
#include "../TGeoObjCircle.h"
#include "../TGeoObj_Utils.h"


void DoObjectsSaveToFile(TGeoObj* Obj) {
	if( (NULL != Obj) && (NULL != GAppDefaultMapFile) ){
		Obj->ListSaveToFile(GAppDefaultMapFile);
	}
}

TGeoObj* DoObjectAddHouse(TGeoObj* Obj, const short x, const short y) {
	TGeoObj* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjHouse();
		LResult->GenTest();
		LResult->setXY(x, y);
	} else {
		if (!(Obj->ListContains(x, y))) {
			LResult = Obj->ListAdd(new TGeoObjHouse());
			LResult->GenTest();
			LResult->setXY(x, y);
		} else {
			LResult = Obj;
		}
	};
	return LResult;
}

TGeoObj* DoObjectAddBank(TGeoObj* Obj, const short x, const short y) {
	TGeoObj* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjBank();
		LResult->GenTest();
		LResult->setXY(x, y);
	}
	else {
		if (!(Obj->ListContains(x, y))) {
			LResult = Obj->ListAdd(new TGeoObjBank());
			LResult->GenTest();
			LResult->setXY(x, y);
		} else {
			LResult = Obj;
		}
	};
	return LResult;
}

TGeoObj* DoObjectAddShop(TGeoObj* Obj, const short x, const short y) {
	TGeoObj* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjShop();
		LResult->GenTest();
		LResult->setXY(x, y);
	}
	else {
		if (!(Obj->ListContains(x, y))) {
			LResult = Obj->ListAdd(new TGeoObjShop());
			LResult->GenTest();
			LResult->setXY(x, y);
		} else {
			LResult = Obj;
		}
	};
	return LResult;
}

TGeoObj* DoObjectAddCircle(TGeoObj* Obj, const short x, const short y) {
	TGeoObj* LResult = NULL;
	if (NULL == Obj) {
		LResult = new TGeoObjCircle();
		LResult->GenTest();
		LResult->setXY(x, y);
	}
	else {
		if (!(Obj->ListContains(x, y))) {
			LResult = Obj->ListAdd(new TGeoObjCircle());
			LResult->GenTest();
			LResult->setXY(x, y);
			((TGeoObjCircle*)LResult)->setR(4);
		} else {
			LResult = Obj;
		}
	};
	return LResult;
}

char* GAppDefaultDocPath = NULL;
char* GAppDefaultMapFile = NULL;

int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// 1.1. Получим стандартные пути 
	GAppDefaultDocPath = Environment::GetFolderPath(Environment::MyDocuments);
	// 1.2. Устанавливаем текущим каталог к папке "Мои докукменты"
	Environment::SetCurrentDir(GAppDefaultDocPath);
	// 1.3. В случае певого запуска - проверить существование подкаталога "Мои докукменты" \ ApplicationFolder
	if (!Directory::Exists(ApplicationFolder)) {
		Directory::Create(ApplicationFolder);
	}
	// 1.4. Собираем в один путь каталог "Мои докукменты" \ ApplicationFolder
	Path::Combine(GAppDefaultDocPath, ApplicationFolder);
	// 1.5. получаем полный путь к файлу "Мои докукменты" \ ApplicationFolder \ DefaultMapFileName
	GAppDefaultMapFile = StringHelper::New();
	strcpy_s(GAppDefaultMapFile, StringHelper::DefaultSize, GAppDefaultDocPath);
	Path::Combine(GAppDefaultMapFile, DefaultMapFileName);


	// очищаем поле консоли для ввода/вывода
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
	// вывод в заголовке программы подсказки с клавишами
	Console::SetColor(Console::clBlack, Console::clLightCyan);
	Console::GotoXY(0, 0);
	int Len = Console::Width() + 1;
	char *TempString = StringHelper::New(Len);
	strcpy_s(TempString, Len, " HELP: (F2) Save | (F4) House | (F5) Bank | (F6) Shop | (F7) Circle | (Del) Delete | (Esc) Exit ");
	while (strlen(TempString) < (Len-1) ) {
		strcat_s(TempString, Len, " ");
	}
	printf("%s", TempString);
	Console::GotoXY(0, 1);

	// Массив географических объектов
	// загрузить массив географических объектов из файла
	TGeoObj* Objects = LoadFromFile(GAppDefaultMapFile);
	
	// Перо для рисования по карте
	TGeoObjTank* Pen = new TGeoObjTank();
	Pen->setX(Console::Width() / 2);
	Pen->setY(Console::Height() / 2);
	Pen->Symbol  = 'o';
	Pen->Color   = Console::clBlack;
	Pen->BgColor = Console::clLightRed;	

	if (NULL != Objects) {
		Objects->ListDraw();
	}
	Pen->Draw();

	int KeyPressed = _getch();
	while (Console::keyEscape != KeyPressed) {
		if ((0xE0 != KeyPressed) && (0 != KeyPressed)) {
			int x = Pen->getX();
			int y = Pen->getY();
			TGeoObj* WasOnObject = NULL;
			if (NULL != Objects) {
				WasOnObject = Objects->ListFindXY(x, y);
			}
			Pen->Erase();
			switch (KeyPressed) {
			    case Console::keyLeft  : {x--; break; };
			    case Console::keyRight : {x++; break; };
			    case Console::keyUp    : {y--; break; };
			    case Console::keyDown  : {y++; break; };
				case Console::keyF2    : {           DoObjectsSaveToFile(Objects);    break; };
				case Console::keyDelete: { Objects = DoObjectDelXY(Objects, x, y); WasOnObject = NULL; break; };
				case Console::keyF4    : { Objects = DoObjectAddHouse(Objects, x, y); break; };
				case Console::keyF5    : { Objects = DoObjectAddBank (Objects, x, y); break; };
				case Console::keyF6    : { Objects = DoObjectAddShop (Objects, x, y); break; };
				case Console::keyF7    : { Objects = DoObjectAddCircle(Objects, x, y); break; };
			}
			if (!(y > 0)) {
				y = 1;
			}
			if (NULL != Objects) {
				Objects->Draw();
				if (NULL != WasOnObject) {
					WasOnObject->Draw();
				}
			}
			Pen->setXY(x, y);
			Pen->Draw();
		}
		KeyPressed = _getch();
	}

	if (NULL != Objects) {
		// сохранить карту объектов в файл
		Objects->ListSaveToFile(GAppDefaultMapFile);
		// высвобождаем память
		Objects = Objects->ListLast();
		while (NULL != Objects) {
			TGeoObj* ItemToDelete = Objects;
			Objects = Objects->Pred;
			delete ItemToDelete;
		}
	}
    // высвобождаем память
	delete Pen;
	free(TempString);
	free(GAppDefaultMapFile);
	free(GAppDefaultDocPath);
	// перед выходом почистим консоль
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
	// установим цвета по-умолчанию
	Console::SetColor(Console::DefaultColor, Console::DefaultBgColor);
}

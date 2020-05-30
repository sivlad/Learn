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
#include "../TGeoObjLine.h"
#include "../TGeoObjCircle.h"
#include "../TGeoObj_Utils.h"

void TankBeforeMove(TGeoObj* Obj) {
	Obj->Erase();
}

void TankAfterMove(TGeoObj* Obj) {
	Obj->Draw();
}

TGeoObj *TankFire(TGeoObjTank* T34, TGeoObjTank::FireVector Vector) {
	TGeoObjLine* LResult = new TGeoObjLine();
	switch (Vector) {
	    case TGeoObjTank::fvLeft: {
			LResult->Symbol = '-';
			LResult->setX(T34->getX()-1);
			LResult->setY(T34->getY());
			LResult->setX2(T34->getX() - T34->FireLength);
			LResult->setY2(T34->getY() );
			break;
	    }
		case TGeoObjTank::fvRight: {
			LResult->Symbol = '-';
			LResult->setX(T34->getX() + 1);
			LResult->setY(T34->getY());
			LResult->setX2(T34->getX() + T34->FireLength);
			LResult->setY2(T34->getY());
			break;
		}
		case TGeoObjTank::fvTop: {
			LResult->Symbol = '|';
			LResult->setX(T34->getX());
			LResult->setY(T34->getY()-1);
			LResult->setX2(T34->getX());
			LResult->setY2(T34->getY() - T34->FireLength);
			break;
		}
		case TGeoObjTank::fvBottom: {
			LResult->Symbol = '|';
			LResult->setX(T34->getX());
			LResult->setY(T34->getY() + 1);
			LResult->setX2(T34->getX());
			LResult->setY2(T34->getY() + T34->FireLength);
			break;
		}
	}
	return LResult;
}

TGeoObj* TankBoom(TGeoObjTank* T34) {
	TGeoObjCircle* LResult = new TGeoObjCircle();
	LResult->setX(T34->getX());
	LResult->setY(T34->getY());
	LResult->setR(10);
	return LResult;
}

TGeoObj* TankPooh(TGeoObjTank* T34) {
	TGeoObj* LResult = new TGeoObj();
	LResult->Color = Console::clLightCyan;
	LResult->Symbol = '%';
	LResult->setX(T34->getX() - 1);
	LResult->setY(T34->getY());
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

	Console::SetScreen();
	// очищаем поле консоли для ввода/вывода
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
	// вывод в заголовке программы подсказки с клавишами
	Console::SetColor(Console::clBlack, Console::clLightCyan);
	Console::GotoXY(0, 0);
	int Len = Console::Width() + 1;
	char* TempString = StringHelper::New(Len);
	strcpy_s(TempString, Len, " HELP: (Esc) Exit ");
	while (strlen(TempString) < (Len - 1)) {
		strcat_s(TempString, Len, " ");
	}
	printf("%s", TempString);
	Console::GotoXY(0, 1);
	// Массив географических объектов
	// загрузить массив географических объектов из файла
	TGeoObj* Objects = LoadFromFile(GAppDefaultMapFile);
    // Создаём и инициализируем танк
	TGeoObjTank* Tank = new TGeoObjTank();
	Tank->setXY(Console::Width() / 2, Console::Height() / 2);
	Tank->Symbol  = 'T';
	Tank->Color   = Console::clBlack;
	Tank->BgColor = Console::clLightGreen;
	Tank->FireLength = 10;
	Tank->BeforeChoordChanged = &TankBeforeMove;
	Tank->ChoordChanged       = &TankAfterMove;
	// первичная отрисовка объектов перед стартом игры
	Tank->Draw();
	if (NULL != Objects) {
		Objects->ListDraw();
	}
	// старт игры
	TGeoObj* Fire = NULL;
	int KeyPressed = _getch();
	while (Console::keyEscape != KeyPressed) {
		if ((0xE0 != KeyPressed) && (0 != KeyPressed)) {
			int x = Tank->getX();
			int y = Tank->getY();
			
			if( NULL != Fire) {
				if (NULL != Objects) {
					TGeoObj* LItem = Objects->ListFirst();
					while ((NULL != LItem) && (NULL != Objects)) {
						TGeoObj* LItemToDel = NULL;
						if (Fire->Contains(LItem->getX(), LItem->getY())) { /// 12 ball !!!
							LItemToDel = LItem;
						}
						LItem = LItem->Next;
						if (NULL != LItemToDel) {
							Objects = DoObjectDelXY(Objects, LItemToDel->getX(), LItemToDel->getY());
						}
					}
				}
				delete Fire;
			}
			Fire = NULL;
			switch (KeyPressed) {
			    case Console::keyLeft : {x--; break; };
			    case Console::keyRight: {x++; break; };
			    case Console::keyUp   : {y--; break; };
			    case Console::keyDown : {y++; break; };
				case Console::keyF5   : {Fire = TankFire(Tank, TGeoObjTank::fvLeft  ); break; };
				case Console::keyF6   : {Fire = TankFire(Tank, TGeoObjTank::fvTop   ); break; };
				case Console::keyF7   : {Fire = TankFire(Tank, TGeoObjTank::fvBottom); break; };
				case Console::keyF8   : {Fire = TankFire(Tank, TGeoObjTank::fvRight ); break; };
				case Console::keyF9   : {Fire = TankBoom(Tank); break; };
				case Console::keyF10  : {Fire = TankPooh(Tank); break; };
			}
			if (!(y > 0)) {
				y = 1;
			}
			if (NULL != Fire) {
				Fire->Draw();
			} 
			if (NULL != Objects) {
				if (!Objects->ListContains(x, y)) {
					Tank->setXY(x, y);
				}
			} else {
				Tank->setXY(x, y);
			}
		}
		KeyPressed = _getch();
	}
    // оссобождение памяти
	delete Tank;
	free(TempString);
	free(GAppDefaultMapFile);
	free(GAppDefaultDocPath);
	// перед выходом почистим консоль
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
	// установим цвета по-умолчанию
	Console::SetColor(Console::DefaultColor, Console::DefaultBgColor);
}
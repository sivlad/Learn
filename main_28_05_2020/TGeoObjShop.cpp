#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObj.h"
#include "TGeoObjShop.h"

TGeoObjShop::TGeoObjShop() {
    setTyp(TGeoObj::gShop);
	Symbol = 'S';
    Square = 0;
	Color = Console::clBlack;
	BgColor = Console::clLightCyan;
}

TGeoObjShop::~TGeoObjShop() {

}

void TGeoObjShop::Print() {
	Console::SetColor(Color);
	printf("SHOP:   %3d [%2d:%2d] %-20s %-40s - %3d  %8.3f\n", Id, getX(), getY(), Name, Address, AddressHouse, Square);
};

void TGeoObjShop::SaveToFile(FILE* FileToSave) {
    fprintf(FileToSave, "TGEOOBJSHOP|%d|%d|%d|%s|%s|%d|%f\n", Id, getX(), getY(), Name, Address, AddressHouse, Square);
}

char* TGeoObjShop::LoadFromString(char* Text) {
	char* LParser2 = TGeoObj::LoadFromString(Text);
	char* LTempSquare = StringHelper::New();
	LParser2 = StringHelper::Parse(LParser2, '|', LTempSquare);
	Square = atof(LTempSquare);
	free(LTempSquare);
	return LParser2;
}

void TGeoObjShop::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "А.Т.Б.\0"
		,"Сильпо\0"
		,"Таврия V\0"
		,"БУМ\0"
		,"Чудо-маркет\0"
	};
	TGeoObj::GenTest();
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	Square = rand() % 1000 + (rand() % 100 / 100.);
}
#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObj.h"
#include "TGeoObjHouse.h"

TGeoObjHouse::TGeoObjHouse() {
	setTyp(TGeoObj::gHouse);
	Symbol = 'H';
	CabCount = 0;
	Color = Console::clYellow;
	BgColor = Console::clBrown;
}

TGeoObjHouse::~TGeoObjHouse() {

}

void TGeoObjHouse::Print() {
	Console::SetColor(Color);
	printf("HOUSE:  %3d [%2d:%2d] %-20s %-40s - %3d  (%d) \n", Id, getX(), getY(), Name, Address, AddressHouse, CabCount);
};

void TGeoObjHouse::SaveToFile(FILE* FileToSave) {
	fprintf(FileToSave, "TGEOOBJHOUSE|%d|%d|%d|%s|%s|%d|%d\n", Id, getX(), getY(), Name, Address, AddressHouse, CabCount);
}

char* TGeoObjHouse::LoadFromString(char* Text) {
	char* LParser2 = TGeoObj::LoadFromString(Text);
	char* LTempCabCount = StringHelper::New();
	LParser2 = StringHelper::Parse(LParser2, '|', LTempCabCount);
	CabCount = atoi(LTempCabCount);
	free(LTempCabCount);
	return LParser2;
}

void TGeoObjHouse::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "Дом купца Иванова\0"
		,"Канатчикова Дача\0"
		,"жил.дом\0"
		,"многоэтажка\0"
		,"частн.дом\0"
	};

	TGeoObj::GenTest();
	
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	CabCount = rand() % 96;
}
#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObj.h"
#include "TGeoObjBank.h"

TGeoObjBank::TGeoObjBank() {
	setTyp(TGeoObj::gBank);
	Symbol = 'B';
	TermCount = 0;
	BankCount = 0;
	Color = Console::clLightGreen;
};

TGeoObjBank::~TGeoObjBank() {

};

void TGeoObjBank::Print() {
	Console::SetColor(Color);
	printf("BANK:   %3d [%2d:%2d] %-20s %-40s - %3d  T=%2d B=%2d \n", Id, getX(), getY(), Name, Address, AddressHouse, TermCount, BankCount);
};


void TGeoObjBank::SaveToFile(FILE* FileToSave) {
	fprintf(FileToSave, "TGEOOBJBANK|%d|%d|%d|%s|%s|%d|%d|%d\n", Id, getX(), getY(), Name, Address, AddressHouse, TermCount, BankCount);
};

char* TGeoObjBank::LoadFromString(char* Text) {
	char* LParser2 = TGeoObj::LoadFromString(Text);
	
	char* LTempTermCount = StringHelper::New();
	char* LTempBankCount = StringHelper::New();
	LParser2 = StringHelper::Parse(LParser2, '|', LTempTermCount);
	LParser2 = StringHelper::Parse(LParser2, '|', LTempBankCount);
	TermCount = atoi(LTempTermCount);
	BankCount = atoi(LTempBankCount);
	free(LTempTermCount);
	free(LTempBankCount);
	
	return LParser2;
}

void TGeoObjBank::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "ПриватБанк\0"
		,"УкрГазБанк\0"
		,"ПУМБ\0"
		,"Альфа-Банк\0"
		,"Нац.Банк\0"
	};
	TGeoObj::GenTest();
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	TermCount = rand() % 3;
	BankCount = rand() % 2;
}
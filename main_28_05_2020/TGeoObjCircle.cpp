#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObj.h"
#include "TGeoObjCircle.h"

TGeoObjCircle::TGeoObjCircle() {
	FR = 0;
	strcpy_s(this->Name, StringHelper::DefaultSize, "TGEOOBJCIRCLE\0");
	Symbol = '*';
	Color  = Console::clLightMagenta;
}

TGeoObjCircle::~TGeoObjCircle(){
	Erase();
}

int TGeoObjCircle::getR() {
	return FR;
}

void TGeoObjCircle::setR(const int aR) {
		if (aR != FR) {
			if (NULL != BeforeChoordChanged) {
				BeforeChoordChanged(this);
			}
			FR = aR;
			if (NULL != ChoordChanged) {
				ChoordChanged(this);
			}
		}
}

void TGeoObjCircle::Draw() {
	Console::SetColor(Color, BgColor);
	for (int LX = (getX() - FR); LX <= (getX() + FR); LX++) {
		for (int LY = (getY() - FR); LY <= (getY() + FR); LY++) {
			if ((pow(getX() - LX,2) + pow(getY() - LY,2)) <= pow(FR,2)) {
				Console::GotoXY(LX, LY);
				printf("%c", Symbol);
			}
		}
	}
}

void TGeoObjCircle::Erase() {
	Console::SetColor(BgColor, BgColor);
	for (int LX = (getX() - FR); LX <=(getX() + FR); LX++) {
		for (int LY = (getY() - FR); LY <= (getY() + FR); LY++) {
			if ((pow(getX() - LX, 2) + pow(getY() - LY, 2)) <= pow(FR, 2)) {
				Console::GotoXY(LX, LY);
				printf(" ");
			}
		}
	}
}

bool TGeoObjCircle::Contains(const int aX, const int aY) {
	return ( (pow((getX() - aX),2) + pow((getY() - aY), 2)) <= pow(FR,2));
}

void TGeoObjCircle::Print() {
	Console::SetColor(Color);
	printf("CIRCLE:  %3d [%2d:%2d] %-20s %-40s - %3d  (%d) \n", Id, getX(), getY(), Name, Address, AddressHouse, getR());
}

void TGeoObjCircle::SaveToFile(FILE* FileToSave) {
	fprintf(FileToSave, "TGEOOBJCIRCLE|%d|%d|%d|%s|%s|%d|%d\n", Id, getX(), getY(), Name, Address, AddressHouse, getR());
}

char* TGeoObjCircle::LoadFromString(char* Text) {
	char* LParser2 = TGeoObj::LoadFromString(Text);
	char* LTempR = StringHelper::New();
	LParser2 = StringHelper::Parse(LParser2, '|', LTempR);
	FR = atoi(LTempR);
	free(LTempR);
	return LParser2;
}

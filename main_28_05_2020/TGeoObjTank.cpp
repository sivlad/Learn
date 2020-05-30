#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObj.h"
#include "TGeoObjTank.h"

TGeoObjTank::TGeoObjTank() {
	strcpy_s(this->Name, StringHelper::DefaultSize, "T-34\0");
	setTyp(gTank);
	Symbol     = 'T';
	FireLength = 0;
	Color      = Console::clBlack;
	BgColor    = Console::clGreen;
}

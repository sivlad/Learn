#include <iostream>
#include "Console.h"
#include "TGeoObj.h"
#include "StringHelper.h"
#include "Console.h"

TGeoObj::TGeoObj() {
	FTyp = gUnknown;
	Symbol = ' ';
	FX = 0;
	FY = 0;
	Id = 0;
	AddressHouse = 0;
	Name    = StringHelper::New();
	Address = StringHelper::New();
	ChoordChanged = NULL;
	Color   = Console::DefaultColor;
	BgColor = Console::DefaultBgColor;
	Next = NULL;
	Pred = NULL;
};

TGeoObj::~TGeoObj() {
	// не порвать двусвязный список
	if (NULL != Pred) { // если удляемый элемент не был первым в ДЛС
		Pred->Next = Next;
	}
	if (NULL != Next) { // если удляемый элемент не был последним в ДЛС
		Next->Pred = Pred;
	}
	free(Address);
	free(Name);
	Erase();
};

TGeoObj *TGeoObj::ListFirst() {
	TGeoObj* LResult = this;
	while (NULL != LResult->Pred) {
		LResult = LResult->Pred;
	}
	return LResult;
}

TGeoObj *TGeoObj::ListLast() {
	TGeoObj* LResult = this;
	while (NULL != LResult->Next) {
		LResult = LResult->Next;
	}
	return LResult;
}

int TGeoObj::ListCount() {
	int LResult = 0;
	TGeoObj* LItem = ListFirst();
	while (NULL != LItem->Next) {
		LResult++;
		LItem = LItem->Next;
	}
	return LResult;
}

TGeoObj* TGeoObj::ListAdd(TGeoObj* ExistingItem) {
	TGeoObj* LResult = ExistingItem;
	LResult->Pred = this;
	LResult->Next = this->Next;
	if (NULL != this->Next) {
	    this->Next->Pred = LResult;
	}
	this->Next = LResult;
	return LResult;
}

bool TGeoObj::ListContains(const int aX, const int aY) {
	bool LResult = false;
	TGeoObj* LItem = ListFirst();
	while (NULL != LItem) {
		if ( LItem->Contains(aX, aY) ) {
			LResult = true;
			break;
		}
		LItem = LItem->Next;
	}
	return LResult;
}

TGeoObj* TGeoObj::ListFindXY(const int aX, const int aY) {
	TGeoObj* LResult = NULL;
	TGeoObj* LItem = ListFirst();
	while (NULL != LItem) {
		if (LItem->Contains(aX, aY)) {
			LResult = LItem;
			break;
		}
		LItem = LItem->Next;
	}
	return LResult;
}

void TGeoObj::ListDraw() {
	TGeoObj* LItem = ListFirst();
	while (NULL != LItem) {
		LItem->Draw();
		LItem = LItem->Next;
	}
}

void  TGeoObj::ListSaveToFile(const char* FileName) {
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "w+");
	if (0 == LFileOpenError) {
		TGeoObj* LItem = ListFirst();
		while (NULL != LItem) {
			LItem->SaveToFile(LFileHandle);
			LItem = LItem->Next;
		}
		fclose(LFileHandle);
	} else {
		Console::GotoXY(20, 20);
		Console::SetColor(Console::clWhite, Console::clLightRed);
		printf(" I cannot to save data into file %s !\n ", FileName);
	}
}

void TGeoObj::GenTest() {
	const int LCNameCount = 5;
	const char* LCName[LCNameCount] = {
		 "цех\0"
		,"пост\0"
		,"сторожка\0"
		,"ларёк\0"
		,"палатка\0"
	};

	const int LCAddressCount = 10;
	const char* LCAddress[LCAddressCount] = {
		 "Дворцовая\0"
		,"Парковая\0"
		,"Ленина\0"
		,"Горького\0"
		,"Орджоникидзе\0"
		,"Лазо\0"
		,"Социалистическая\0"
		,"Юбилейная\0"
		,"Крмаматорский\0"
		,"Нади Курченко\0"
	};
	FX = rand() % Console::Width ();
	FY = rand() % Console::Height();
	int r = rand() % LCNameCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCName[r]);
	r = rand() % LCAddressCount;
	strcpy_s(Address, StringHelper::DefaultSize, LCAddress[r]);
	AddressHouse = rand() % 100;
}

void TGeoObj::SaveToFile(FILE* FileToSave) {
	fprintf(FileToSave, "TGEOOBJ|%d|%d|%d|%s|%s|%d\n", Id, FX, FY, Name, Address, AddressHouse);
}

char* TGeoObj::LoadFromString(char* Text) {
	char* LParser = Text;
	char* LTempClassName = StringHelper::New();
	char* LTempId = StringHelper::New();
	char* LTempFX = StringHelper::New();
	char* LTempFY = StringHelper::New();
	char* LTempName = StringHelper::New();
	char* LTempAddress = StringHelper::New();
	char* LTempAddressHouse = StringHelper::New();

	LParser = StringHelper::Parse(LParser, '|', LTempClassName);
	LParser = StringHelper::Parse(LParser, '|', LTempId);
	LParser = StringHelper::Parse(LParser, '|', LTempFX);
	LParser = StringHelper::Parse(LParser, '|', LTempFY);
	LParser = StringHelper::Parse(LParser, '|', LTempName);
	LParser = StringHelper::Parse(LParser, '|', LTempAddress);
	LParser = StringHelper::Parse(LParser, '|', LTempAddressHouse);

	Id = atoi(LTempId);
	FX = atoi(LTempFX);
	FY = atoi(LTempFY);
	StringHelper::Null(Name);
	strcpy_s(Name, StringHelper::DefaultSize, LTempName);
	StringHelper::Null(LTempAddress);
	strcpy_s(Address, StringHelper::DefaultSize, LTempAddress);
	AddressHouse = atoi(LTempAddressHouse);

	free(LTempAddressHouse);
	free(LTempAddress);
	free(LTempName);
	free(LTempFY);
	free(LTempFX);
	free(LTempId);
	free(LTempClassName);
	
	return LParser;
}

void TGeoObj::Print() {
	Console::SetColor(Color);
	printf("UNKNOWN %3d [%2d:%2d] %-20s %-40s - %3d \n", Id, FX, FY, Name, Address, AddressHouse);
}

void TGeoObj::Draw() {
	Console::SetColor(Color, BgColor);
	Console::GotoXY(FX, FY);
	printf("%c", Symbol);
	Console::GotoXY(FX, FY);
}

void TGeoObj::Erase() {
	Console::SetColor(Console::DefaultBgColor);
	Console::GotoXY(FX, FY);
	printf(" ");
	Console::GotoXY(FX, FY);
}


TGeoObj::Type TGeoObj::getTyp() {
	return FTyp;
};

void TGeoObj::setTyp(const TGeoObj::Type aTyp) {
	if (aTyp != FTyp) {
		FTyp = aTyp;
	}
};

int  TGeoObj::getX() {
	return FX;
};

void TGeoObj::setX(const int aX) {
	if ( (aX >= 0) && (aX < Console::Width() ) ) {
		if (aX != FX) {
			if (NULL != BeforeChoordChanged) {
				BeforeChoordChanged(this);
			}
			FX = aX;
			if (NULL != ChoordChanged) {
				ChoordChanged( this );
			}
		}
	}
};

int TGeoObj::getY() {
	return FY;
};

void TGeoObj::setY(const int aY) {
	if ( (aY >= 0) && (aY < Console::Height()) ) {
		if (aY != FY) {
			if (NULL != BeforeChoordChanged) {
				BeforeChoordChanged(this);
			}
			FY = aY;
			if (NULL != ChoordChanged) {
				ChoordChanged(this);
			}
		}
	}
};

void TGeoObj::setXY(const int aX, const int aY) {
	int LX = aX;
	int LY = aY;
	if(!((aX >= 0) && (aX < Console::Width()))){
		LX = getX();
	}
	if(!((aY >= 0) && (aY < Console::Height()))){
		LY = getY();
	}
	if ( (LX != FX) || (LY != FY)) {
		if (NULL != BeforeChoordChanged) {
			BeforeChoordChanged(this);
		}
		FX = LX;
		FY = LY;
		if (NULL != ChoordChanged) {
			ChoordChanged(this);
		}
	}
}

bool TGeoObj::Contains(const int aX, const int aY) {
	return ( (FX == aX) && (FY == aY) );
}
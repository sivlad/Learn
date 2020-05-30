#include <iostream>
#include "StringHelper.h"
#include "Console.h"
#include "TGeoObj.h"
#include "TGeoObjLine.h"

TGeoObjLine::TGeoObjLine() {
	strcpy_s(this->Name, StringHelper::DefaultSize, "TGEOOBJLINE\0");
	Symbol = '-';
	Color  = Console::clRed;
}

TGeoObjLine::~TGeoObjLine() {
//	TGeoObj::~TGeoObj();
	Erase();
}


int TGeoObjLine::getX2() {
	return FX2;
};

void TGeoObjLine::setX2(const int aX2) {
	if ((aX2 >= 0) && (aX2 < Console::Width())) {
		if (aX2 != FX2) {
			if (NULL != BeforeChoordChanged) {
				BeforeChoordChanged(this);
			}
			FX2 = aX2;
			if (NULL != ChoordChanged) {
				ChoordChanged(this);
			}
		}
	}
};

int TGeoObjLine::getY2() {
	return FY2;
};

void TGeoObjLine::setY2(const int aY2) {
	if ((aY2 >= 0) && (aY2 < Console::Height())) {
		if (aY2 != FY2) {
			if (NULL != BeforeChoordChanged) {
				BeforeChoordChanged(this);
			}
			FY2 = aY2;
			if (NULL != ChoordChanged) {
				ChoordChanged(this);
			}
		}
	}
};

void TGeoObjLine::setXY2(const int aX2, const int aY2) {
	int LX2 = aX2;
	int LY2 = aY2;
	if (!((aX2 >= 0) && (aX2 < Console::Width()))) {
		LX2 = getX2();
	}
	if (!((aY2 >= 0) && (aY2 < Console::Height()))) {
		LY2 = getY2();
	}
	if ((LX2 != FX2) || (LY2 != FY2)) {
		if (NULL != BeforeChoordChanged) {
			BeforeChoordChanged(this);
		}
		FX2 = LX2;
		FY2 = LY2;
		if (NULL != ChoordChanged) {
			ChoordChanged(this);
		}
	}
}

void TGeoObjLine::Draw() {
	Console::SetColor(Color, BgColor);
	int LXBegin = getX();
	int LXEnd   = FX2;
	if (LXBegin > LXEnd) {
		LXBegin = FX2;
		LXEnd   = getX();
	}
	short LYBegin = getY();
	short LYEnd   = FY2;
	if (LYBegin > LYEnd) {
		LYBegin = FY2;
		LYEnd = getY();
	}
	if( (LXEnd - LXBegin) == 0){ // для вертикальной прямой
		int LX = LXBegin;
		for (int LY = LYBegin; LY <= LYEnd; LY++) {
			Console::GotoXY(LX, LY);
			printf("%c", Symbol);
		}
	} else {
		for (int LX = LXBegin; LX <= LXEnd; LX++) {
			int LY = LYBegin + (LYEnd - LYBegin) / (LXEnd - LXBegin) * (LX - LXBegin);
			Console::GotoXY(LX, LY);
			printf("%c", Symbol);
		}
	}
}

void TGeoObjLine::Erase() {
	Console::SetColor(BgColor, BgColor);
	int LXBegin = getX();
	int LXEnd = FX2;
	if (LXBegin > LXEnd) {
		LXBegin = FX2;
		LXEnd = getX();
	}
	int LYBegin = getY();
	int LYEnd = FY2;
	if (LYBegin > LYEnd) {
		LYBegin = FY2;
		LYEnd = getY();
	}
	if ((LXEnd - LXBegin) == 0) { // для вертикальной прямой
		int LX = LXBegin;
		for (int LY = LYBegin; LY <= LYEnd; LY++) {
			Console::GotoXY(LX, LY);
			printf(" ");
		}
	} else {
		for (int LX = LXBegin; LX <= LXEnd; LX++) {
			int LY = LYBegin + (LYEnd - LYBegin) / (LXEnd - LXBegin) * (LX - LXBegin);
			Console::GotoXY(LX, LY);
			printf(" ");
		}
	}
}

bool TGeoObjLine::Contains(const int aX, const int aY) {
	bool LResult = false;
	if( getX() == getX2() ) { // вертикальная прямая
		if (getX() == aX) {
			int LYBeg = getY();
			int LYEnd = getY2();
			if (LYBeg > LYEnd) { // в том случае, когда конечная точка прямой - выше начальной
				LYBeg = getY2();
				LYEnd = getY();
			}
			for (int LY = LYBeg; LY <= LYEnd; LY++) {
				if (LY == aY) {
					LResult = true;
					break;
				}
			}
		}
	} else if (getY() == getY2()) { // горизонтальная прямая
		if (getY() == aY) {
			int LXBeg = getX();
			int LXEnd = getX2();
			if (LXBeg > LXEnd) { // в том случае, когда конечная точка прямой - левее начальной
				LXBeg = getX2();
				LXEnd = getX();
			}
			for (int LX = LXBeg; LX <= LXEnd; LX++) {
				if (LX == aX) {
					LResult = true;
					break;
				}
			}
		}
	} else { // произвольная прямая
		for (int LX = getX(); LX <= getX2(); LX++) {
			int LY = getY() + (getY2() - getY()) / (getX2() - getX()) * (LX - getX());
			if ( (aX == LX) && (aY == LY) ) {
				LResult = true;
				break;
			}
		}
	}
	return LResult;
}
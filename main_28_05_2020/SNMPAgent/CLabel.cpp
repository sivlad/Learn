#include "CLabel.h"
#include "..\StringHelper.h"

CLabel::CLabel() {

}

CLabel::~CLabel() {
}

void CLabel::FormCreate() {

}

void CLabel::FormShow(HDC aOutputDC) {

}

void CLabel::FormDraw() {

}

void CLabel::FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC) {
	BitBlt(aHdcDest, FPosition.left, FPosition.top, FWidth, FHeight, aHdcSourth, aPosInSourthDC.x, aPosInSourthDC.y, SRCCOPY);
	SetBkColor(aHdcDest, RGB(96, 131, 159));
	SetTextColor(aHdcDest, RGB(255, 255, 255));
	TextOutA(aHdcDest, this->FPosition.left + 5, this->FPosition.top + 10, this->FCaaption, strlen(this->FCaaption));

}

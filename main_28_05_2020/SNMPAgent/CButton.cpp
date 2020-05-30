#include "CButton.h"

void CButton::FormCreate()  {
}

void CButton::FormShow(HDC aOutputDC) {

}

void CButton::FormDraw() {

}

void CButton::FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC) {
	BitBlt(aHdcDest, FPosition.left, FPosition.top, FWidth, FHeight, aHdcSourth, aPosInSourthDC.x, aPosInSourthDC.y, SRCCOPY);
}

void CButton::DoOnButtonClick(Application* Sender) { if (NULL != OnButtonClick) OnButtonClick(this, Sender); }

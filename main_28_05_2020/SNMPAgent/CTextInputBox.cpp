#include "CTextInputBox.h"

void CTextInputBox::FormCreate() {

}

void CTextInputBox::FormShow(HDC aOutputDC) {

}

void CTextInputBox::FormDraw() {

}

void CTextInputBox::FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC) {
	BitBlt(aHdcDest, FPosition.left, FPosition.top, FWidth, FHeight, aHdcSourth, aPosInSourthDC.x, aPosInSourthDC.y, SRCCOPY);
	SetBkColor(aHdcDest, RGB(185, 212, 231));
	SetTextColor(aHdcDest, RGB(0, 0, 0));
	TextOutA(aHdcDest, this->FPosition.left + 5, this->FPosition.top + 10, this->FCaaption, strlen(this->FCaaption));
}

void CTextInputBox::DoOnTextInput(Application* Sender) { if (NULL != OnTextInput) OnTextInput(this,Sender); }

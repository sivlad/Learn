#include "COutputArea.h"


void COutputArea::FormDraw(HDC aHdcDest) {
	HBRUSH LBackgroundBrush = CreateSolidBrush(RGB(96, 131, 159));
	HBRUSH LOldBrush = (HBRUSH)SelectObject(aHdcDest, LBackgroundBrush);
	Rectangle(aHdcDest, FPosition.left, FPosition.top, FPosition.right, FPosition.bottom);
	SelectObject(aHdcDest, LOldBrush);
	DeleteObject(SelectObject(aHdcDest, LBackgroundBrush));

}

void COutputArea::FormTextOut(HDC aHdcDest, CMonitoredObject* aMonitoredObject) {
	POINT OutputPos;
	OutputPos.x = FPosition.left + 10;
	OutputPos.y = FPosition.top + 10;
	int flag_sdvig = 0;

	SetBkColor(aHdcDest, RGB(96, 131, 159));
	SetTextColor(aHdcDest, RGB(255, 255, 255));
	TextOutA(aHdcDest, OutputPos.x, OutputPos.y, aMonitoredObject->FName, strlen(aMonitoredObject->FName));
	OutputPos.x += 10;
	OutputPos.y += 20;
	for (CPort* LPort : aMonitoredObject->FMonitoredInstance) {
		TextOutA(aHdcDest, OutputPos.x, OutputPos.y, LPort->FName, strlen(LPort->FName));
		OutputPos.y += 20;
		for (CMonitoredParam* LMonitoredParam : LPort->FMonitoredParam) {
			if (0 == flag_sdvig) {
				OutputPos.x += 10;
				flag_sdvig = 1;
			}
			TextOutA(aHdcDest, OutputPos.x, OutputPos.y, LMonitoredParam->FName, strlen(LMonitoredParam->FName));
			OutputPos.y += 20;
		}
		OutputPos.x -= 10;
		flag_sdvig = 0;
	}

}

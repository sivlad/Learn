#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include "SNMPAgent/CMonitoredObject.h"
#include "SNMPAgent/CMapObjectItem.h"
#include "SNMPAgent/CAddForm.h"

struct MyColor {
	int A;
	int R;
	int G;
	int B;
};


class Application;

typedef void(*FuncOnKey)(Application* Sender);

class Application {
private:
	POINT FShow_GraphikPoint;

public:
	int PressedKey;
	bool Running;
	bool MonitoringON;
	bool MouseLBDown;
	bool MainFormAnalisMapObj;

	CAddForm* FAddForm;

	HDC Mainform;
	HBITMAP MainFormBitmap;
	HDC MainformPressed;
	HBITMAP MainFormPressedBitmap;
	HDC MainformNotPressed;
	HBITMAP MainFormNotPressedBitmap;
	HDC GraphikHDC;
	HBITMAP GraphikBitmap;

	HDC Frame;
	HBITMAP FrameBitmap;

	std::vector<CMonitoredObject*> MonitoredObj;
	std::vector<CMapObjectItem*> MapObject;

	CMonitoredObject* FAddedMonitoredObject;

	Application();
	~Application();
	virtual void Run();
	virtual void DoProcessKey(const int AKeyPressed);
	FuncOnKey OnEscape;
	FuncOnKey OnLeft;
	FuncOnKey OnRight;
	FuncOnKey OnUp;
	FuncOnKey OnDown;
	FuncOnKey OnF1;
	FuncOnKey OnF2;
	FuncOnKey OnF3;
	FuncOnKey OnF4;
	FuncOnKey OnF5;
	FuncOnKey OnF6;
	FuncOnKey OnF7;
	FuncOnKey OnF8;
	FuncOnKey OnF9;
	FuncOnKey OnF10;
	FuncOnKey OnF11;
	FuncOnKey OnF12;
protected:
	virtual void LoadGraficRes(char* aFileName);
	virtual void Show();
	virtual void DoAfterCreate();
	virtual void FindInPressedMap(POINT aCursorPos);
	virtual void AddMonitoredObj();
	virtual void AddMonitoredObj(char* aName, char* aIpAdress, char* aVersionSNMP, char* aConectionString);
	virtual void SaveConfMonitoredObj(CMonitoredObject* aMonObj);
	virtual void LoadConfMonitoredObj();
	virtual void SaveConfMonitoredObjAll();
	virtual void GraphikPaint(CMonitoredParam* aMonitoredParam, CMapObjectItem* aMapObjectItem);
	virtual void GraphikShow(CMapObjectItem* aMapObjectItem);
	virtual void LoadMapObj();
	virtual void AddMapObjItem(char* aName, int aLeft, int aTop, int aright, int aBottom, int aWidth, int aHeight, char* aCaption, char* aConteiner_Name);
	virtual CMapObjectItem* FindMapObject(char* aName);
	virtual void GraphikReDraw();
	virtual void CreateStartFrame();
	virtual void ReDrawMonitoringButton(CMapObjectItem* Sender);
	virtual void ReDrawAddButton(CMapObjectItem* Sender);


	virtual void DoOnKeyEscape();
	virtual void DoOnKeyLeft();
	virtual void DoOnKeyRight();
	virtual void DoOnKeyUp();
	virtual void DoOnKeyDown();
	virtual void DoOnKeyF1();
	virtual void DoOnKeyF2();
	virtual void DoOnKeyF3();
	virtual void DoOnKeyF4();
	virtual void DoOnKeyF5();
	virtual void DoOnKeyF6();
	virtual void DoOnKeyF7();
	virtual void DoOnKeyF8();
	virtual void DoOnKeyF9();
	virtual void DoOnKeyF10();
	virtual void DoOnKeyF11();
	virtual void DoOnKeyF12();
	virtual void DoOnMonitoringButton();
	virtual void DoMonitoringButtonClick(CMapObjectItem* Sender);
	virtual void DoAddButtonClick(CMapObjectItem* Sender);
	virtual void DoGraphikAreaClick(CMapObjectItem* aMapObjectItem);

};

#endif
#ifndef TGEOOBJ_H
#define TGEOOBJ_H

#include "Console.h"

class TGeoObj;

typedef void (*funcOnChoordChanged) (TGeoObj* Obj);

class TGeoObj {
public: // поля и методя доступны только этому классу и классам-потомкам, доступны "снаружи"
	static enum Type {
		gUnknown,   // 0
		gHouse,     // 1
		gShop,      // 2
		gBank,      // 3
		gTank       // 4
	};
	int Id;
	char* Name;
	char* Address;
	int AddressHouse;
	char Symbol;
	Console::ConsoleColors Color;
	Console::ConsoleColors BgColor;
	funcOnChoordChanged BeforeChoordChanged;
	funcOnChoordChanged ChoordChanged;
	TGeoObj();
	virtual ~TGeoObj();
	virtual void Print();
	virtual void Draw();
	virtual void Erase();
	virtual Type getTyp();
	virtual int getX();
	virtual void setX(const int aX);
	virtual int getY();
	virtual void setY(const int aY);
	virtual void setXY(const int aX, const int aY);
	virtual void SaveToFile(FILE* FileToSave);
	virtual char* LoadFromString(char* Text);
	virtual void GenTest();
	virtual bool Contains(const int aX, const int aY);
public:
	TGeoObj* Next;
	TGeoObj* Pred;
	virtual TGeoObj *ListFirst();
	virtual TGeoObj *ListLast();
	virtual int ListCount();
	virtual TGeoObj* ListAdd(TGeoObj* ExistingItem);
	virtual bool ListContains(const int aX, const int aY);
	virtual TGeoObj* ListFindXY(const int aX, const int aY);
	virtual void ListDraw();
	virtual void ListSaveToFile(const char *FileName);
protected: // поля и методя доступны только этому классу и классам-потомкам, НЕ доступны "снаружи"
	virtual void setTyp(const Type aTyp);
private: // поля и методы в этой секции доступны только этому классу, НЕ доступны "снаружи"
	Type FTyp;
	int FX;
	int FY;
};


#endif


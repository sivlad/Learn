#ifndef TGEOOBJHOUSE_H
#define TGEOOBJHOUSE_H

#include "TGeoObj.h"

class TGeoObjHouse : public TGeoObj {
public:
	int CabCount;
	TGeoObjHouse();
	~TGeoObjHouse();
	virtual void Print();
	virtual void SaveToFile(FILE* FileToSave);
	virtual void GenTest();
	virtual char* LoadFromString(char* Text);
};

#endif
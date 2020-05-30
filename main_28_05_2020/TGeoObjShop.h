#ifndef TGEOOBJSHOP_H
#define TGEOOBJSHOP_H

#include "TGeoObj.h"

class TGeoObjShop : public TGeoObj {
public:
	double Square;
	TGeoObjShop();
	~TGeoObjShop();
	virtual void Print();
	virtual void SaveToFile(FILE* FileToSave);
	virtual void GenTest();
	virtual char* LoadFromString(char* Text);
};

#endif
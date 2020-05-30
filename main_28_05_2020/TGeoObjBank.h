#ifndef TGEOOBJBANK_H
#define TGEOOBJBANK_H

#include "TGeoObj.h"
class TGeoObjBank : public TGeoObj {
public:
	int TermCount;
	int BankCount;
	TGeoObjBank();
	~TGeoObjBank();
	virtual void Print();
	virtual void SaveToFile(FILE* FileToSave);
	virtual char* LoadFromString(char* Text);
	virtual void GenTest();
};

#endif
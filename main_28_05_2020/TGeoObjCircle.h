#ifndef TGEOOBJECTCIRCLE_H
#define TGEOOBJECTCIRCLE_H

#include "TGeoObj.h"

class TGeoObjCircle :public TGeoObj {
public:
	TGeoObjCircle();
	virtual ~TGeoObjCircle();
	virtual int getR();
	virtual void setR(const int aR);
	virtual void Draw();
	virtual void Erase();
	virtual bool Contains(const int aX, const int aY);
	virtual void Print();
	virtual void SaveToFile(FILE* FileToSave);
	virtual char* LoadFromString(char* Text);
private:
	int FR;
};

#endif

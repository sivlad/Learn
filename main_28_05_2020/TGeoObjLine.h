#ifndef TGEOOBJLINE_H
#define TGEOOBJLINE_H

#include "TGeoObj.h"

class TGeoObjLine :public TGeoObj {
public:
	TGeoObjLine();
	virtual ~TGeoObjLine();
	virtual int getX2();
	virtual void setX2(const int aX2);
	virtual int getY2();
	virtual void setY2(const int aY2);
	virtual void setXY2(const int aX2, const int aY2);
	virtual void Draw();
	virtual void Erase();
	virtual bool Contains(const int aX, const int aY);
private:
	short FX2;
	short FY2;
};

#endif

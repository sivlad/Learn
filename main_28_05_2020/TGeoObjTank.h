#ifndef TOBJTANK_H
#define TOBJTANK_H

#include "TGeoObj.h"

class TGeoObjTank : public TGeoObj {
public:
	static enum FireVector { fvLeft, fvTop, fvRight, fvBottom };
public:
	short int FireLength;
	TGeoObjTank();
};

#endif


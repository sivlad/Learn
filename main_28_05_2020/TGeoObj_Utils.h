#ifndef TGEOOBJ_UTILS_H
#define TGEOOBJ_UTILS_H

#include "TGeoObj.h"
#include "TGeoObjBank.h"
#include "TGeoObjShop.h"
#include "TGeoObjHouse.h"
#include "TGeoObjCircle.h"

TGeoObj* LoadFromFile(const char* FileName);
TGeoObj* DoObjectDelXY(TGeoObj* Obj, const short x, const short y);

#endif
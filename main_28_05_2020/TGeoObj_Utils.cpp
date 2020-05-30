#include <iostream>
#include "TGeoObj_Utils.h"
#include "StringHelper.h"

TGeoObj* LoadFromFile(const char* FileName) {
	TGeoObj* LResult = NULL;
	FILE* LFileHandle;
	int LFileOpenError = fopen_s(&LFileHandle, FileName, "r");
	if (0 == LFileOpenError) {
		char* LClassName = StringHelper::New();
		char* LBuffer = StringHelper::New(StringHelper::DefaultBufferSize);
		char* LWork = LBuffer;
		while (!feof(LFileHandle)) {
			*LWork = fgetc(LFileHandle);
			if ('\n' == *LWork) {
				*LWork = '|';
				StringHelper::Parse(LBuffer, '|', LClassName);
				if (0 == strcmp(LClassName, "TGEOOBJHOUSE")) {
					if (NULL == LResult) {
						LResult = new TGeoObjHouse();
					} else {
						LResult = LResult->ListAdd(new TGeoObjHouse());
					}
				} else if (0 == strcmp(LClassName, "TGEOOBJSHOP")) {
					if (NULL == LResult) {
						LResult = new TGeoObjShop();
					} else {
						LResult = LResult->ListAdd(new TGeoObjShop());
					}
				} else if (0 == strcmp(LClassName, "TGEOOBJBANK")) {
					if (NULL == LResult) {
						LResult = new TGeoObjBank();
					} else {
						LResult = LResult->ListAdd(new TGeoObjBank());
					}
				} else if (0 == strcmp(LClassName, "TGEOOBJCIRCLE")) {
					if (NULL == LResult) {
						LResult = new TGeoObjCircle();
					}
					else {
						LResult = LResult->ListAdd(new TGeoObjCircle());
					}
			    }
				if (NULL != LResult) {
					LResult->LoadFromString(LBuffer);
				}
				StringHelper::Null(LBuffer, StringHelper::DefaultBufferSize);
				LWork = LBuffer;
			} else {
				LWork++;
			}
		}
		fclose(LFileHandle);
	}
	else {

	}
	return LResult;
}

TGeoObj* DoObjectDelXY(TGeoObj* Obj, const short x, const short y) {
	TGeoObj* LResult = Obj;
	if (NULL != LResult) {
		TGeoObj* LItemToDelete = LResult->ListFindXY(x, y);
		while (NULL != LItemToDelete) {
			if (LItemToDelete == LResult) {
				if (NULL != LItemToDelete->Pred) {
					LResult = LItemToDelete->Pred;
				} else if (NULL != LItemToDelete->Next) {
					LResult = LItemToDelete->Next;
				} else {
					LResult = NULL;
				}
			}
			delete LItemToDelete;
			LItemToDelete = NULL;
			if (NULL != LResult) {
				LItemToDelete = LResult->ListFindXY(x, y);
			}
		}
	}
	return LResult;
}

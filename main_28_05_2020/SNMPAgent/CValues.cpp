#include "CValues.h"
#include "..\StringHelper.h"
#include <stdlib.h>


CValues::CValues() {
	FDate = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FDate, StringHelper::DefaultBufferSize);
	FTime = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FTime, StringHelper::DefaultBufferSize);
	FValue = 0;
	FDelta = 0;
}

CValues::~CValues() {
	free(FDate);
	free(FTime);
}

#include "CHost.h"
#include "..\StringHelper.h"

CHost::CHost() {
	FName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
}

CHost::~CHost() {
	free(FName);
}
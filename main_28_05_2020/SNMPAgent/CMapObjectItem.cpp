#include "CMapObjectItem.h"
#include "..\StringHelper.h"
#include "..\Application.h"

CMapObjectItem::CMapObjectItem() {
	
	FConteiner_Name = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FConteiner_Name, StringHelper::DefaultBufferSize);
	FName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FName, StringHelper::DefaultBufferSize);
	FCaption = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FCaption, StringHelper::DefaultBufferSize);

	FWidth = 0;
	FHeight = 0;
	FPosition = { 0,0,0,0 };
	FPressed = false;
	FVisible = false;
}


CMapObjectItem::~CMapObjectItem() {
	free(FName);
	free(FCaption);
	free(FConteiner_Name);
}


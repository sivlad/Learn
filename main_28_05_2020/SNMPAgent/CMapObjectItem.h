#pragma once

#ifndef COBJECTMAP_H
#define COBJECTMAP_H

#include <Windows.h>
//#include "..\Application.h"

class CMapObjectItem
{ 
public:
	char* FConteiner_Name;
	char* FName;
	char* FCaption;
	RECT FPosition;
	int FWidth;
	int FHeight;
	bool FPressed;
	bool FVisible;


	CMapObjectItem();
	~CMapObjectItem();

};

#endif
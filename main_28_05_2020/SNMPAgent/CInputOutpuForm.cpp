#include "CInputOutpuForm.h"
#include "..\StringHelper.h"
#include "../Application.h"


CInputOutpuForm::CInputOutpuForm() {
	FName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FName, StringHelper::DefaultBufferSize);
	FCaaption = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FCaaption, StringHelper::DefaultBufferSize);
	FVisible = false;
	FWidth = 0;
	FHeight = 0;
	FPresseed = false;

}

CInputOutpuForm::~CInputOutpuForm() {
	free (FName);
	free(FCaaption);
}

void CInputOutpuForm::FormCreate() {

}

void CInputOutpuForm::FormShow(HDC aOutputDC) {

}


void CInputOutpuForm::FormDraw() {

}

void CInputOutpuForm::FormDraw(HDC aHdcDest, HDC aHdcSourth, POINT aPosInSourthDC)
{

}

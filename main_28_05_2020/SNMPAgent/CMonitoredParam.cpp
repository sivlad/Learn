#include "CMonitoredParam.h"
#include "..\StringHelper.h"

#define BACKCOLOR_GRAPHIK 255, 255, 255;


CMonitoredParam::CMonitoredParam() {
	FName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FName, StringHelper::DefaultBufferSize);
	FSNMPComand = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FSNMPComand, StringHelper::DefaultBufferSize);
	FLogfileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FLogfileName, StringHelper::DefaultBufferSize);
}

CMonitoredParam::~CMonitoredParam() {
	free(FName);
	free(FSNMPComand);
	free(FLogfileName);

	for (CValues* LTempValue : FValues) {
		delete(LTempValue);
	}
}

void CMonitoredParam::AddCValues() {

}

void CMonitoredParam::SaveCValues(CValues* aValues) {

}

void CMonitoredParam::AddCValues(char* aDate, char* aTime, long int aValue) {
	CValues* LValue = new CValues();
	strcpy_s(LValue->FDate, StringHelper::DefaultBufferSize, aDate);
	strcpy_s(LValue->FTime, StringHelper::DefaultBufferSize, aTime);
	LValue->FValue = aValue;
	FValues.push_back(LValue);
}


void CMonitoredParam::LoadValues() {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, FLogfileName);

	int FileOpenError = fopen_s(&MyFile, FileName, "r");
	if (0 == FileOpenError) {
		char* Buffer = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);

		char* LData = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LData, StringHelper::DefaultBufferSize);
		char* LTime = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LTime, StringHelper::DefaultBufferSize);
		char* LValue = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LValue, StringHelper::DefaultBufferSize);

		char* parser = NULL;
		int flag = 0;

		char* Work = Buffer;
		while (!feof(MyFile)) {
			*Work = fgetc(MyFile);
			if (*Work != '\n') {
				Work++;
			}
			else {
				parser = Buffer;
				//					parser = StringHelper::Parse(parser, ' ', LA, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LData, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '|', LTime, StringHelper::DefaultBufferSize);
				parser = StringHelper::Parse(parser, '\n', LValue, StringHelper::DefaultBufferSize);

				StringHelper::Null(Buffer, StringHelper::DefaultBufferSize);
				Work = Buffer;
				AddCValues(LData, LTime, atol(LValue));

			}
		}
		free(Buffer);
		free(LData);
		free(LTime);
		free(LValue);
		free(FileName);

		fclose(MyFile);
	}

}

void CMonitoredParam::CountDelta() {
	if (FValues.size() > 0) {
		int LTime = 0;
		int LTime_pred = 0;
		char* parser;
		char* LH = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LH, StringHelper::DefaultBufferSize);
		char* LM = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
		StringHelper::Null(LM, StringHelper::DefaultBufferSize);
		int LH_int = 0;
		int LM_int = 0;
		int LH_pred_int = 0;
		int LM_pred_int = 0;

		parser = FValues[0]->FTime;
		parser = StringHelper::Parse(parser, ':', LH, StringHelper::DefaultBufferSize);
		strcpy_s(LM, StringHelper::DefaultBufferSize, parser);
		LH_pred_int = atoi(LH);
		LM_pred_int = atoi(LM);
		LTime_pred = LH_pred_int * 60 + LM_pred_int;

		for (int i = 1; i < FValues.size(); i++) {

			parser = FValues[i]->FTime;
			parser = StringHelper::Parse(parser, ':', LH, StringHelper::DefaultBufferSize);
			strcpy_s(LM, StringHelper::DefaultBufferSize, parser);
			LH_int = atoi(LH);
			LM_int = atoi(LM);
			LTime = LH_int * 60 + LM_int;
			if (1 == (LTime - LTime_pred)) {
				FValues[i]->FDelta = FValues[i]->FValue - FValues[i - 1]->FValue;
			}
			LTime_pred = LTime;
		}
	}

}

void CMonitoredParam::CountDelta(int aPos) {
	int LTime = 0;
	int LTime_pred = 0;
	char* parser;
	char* LH = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(LH, StringHelper::DefaultBufferSize);
	char* LM = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(LM, StringHelper::DefaultBufferSize);
	int LH_int = 0;
	int LM_int = 0;
	int LH_pred_int = 0;
	int LM_pred_int = 0;

	parser = FValues[aPos]->FTime;
	parser = StringHelper::Parse(parser, ':', LH, StringHelper::DefaultBufferSize);
	strcpy_s(LM, StringHelper::DefaultBufferSize, parser);
	LH_pred_int = atoi(LH);
	LM_pred_int = atoi(LM);
	LTime_pred = LH_pred_int * 60 + LM_pred_int;

	for (int i = aPos+1; i < FValues.size(); i++) {

		parser = FValues[i]->FTime;
		parser = StringHelper::Parse(parser, ':', LH, StringHelper::DefaultBufferSize);
		strcpy_s(LM, StringHelper::DefaultBufferSize, parser);
		LH_int = atoi(LH);
		LM_int = atoi(LM);
		LTime = LH_int * 60 + LM_int;
		if (1 == (LTime - LTime_pred)) {
			FValues[i]->FDelta = FValues[i]->FValue - FValues[i - 1]->FValue;
		}
		LTime_pred = LTime;
	}

}

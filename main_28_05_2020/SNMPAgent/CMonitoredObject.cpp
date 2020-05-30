#include "CMonitoredObject.h"
#include "..\StringHelper.h"


CMonitoredObject::CMonitoredObject() {

	FName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FName, StringHelper::DefaultBufferSize);
	FIpAdress = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FIpAdress, StringHelper::DefaultBufferSize);
	FVersionSNMP = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FVersionSNMP, StringHelper::DefaultBufferSize);
	FConectionString = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FConectionString, StringHelper::DefaultBufferSize);

//	for (int i = 0; i < 3; i++) {
//		AddMonitoredInstance();
//	}
}

CMonitoredObject::~CMonitoredObject() {
	free(FName);
	free(FIpAdress);
	free(FVersionSNMP);
	free(FConectionString);
	for (CPort* LMonitoredInstance : FMonitoredInstance) {
//		SaveConfMonitoredInstance(LMonitoredInstance);
		delete(LMonitoredInstance);
	}

}

void CMonitoredObject::AddMonitoredInstance() {
	CPort* LPort = new CPort();
	strcpy_s(LPort->FName, StringHelper::DefaultBufferSize, "LAN interface");
	FMonitoredInstance.push_back(LPort);
}

void CMonitoredObject::AddMonitoredInstance(char* aName) {
	CPort* LPort = new CPort();
	strcpy_s(LPort->FName, StringHelper::DefaultBufferSize, aName);
	FMonitoredInstance.push_back(LPort);
}


void CMonitoredObject::SaveConfMonitoredInstance(CPort* aPort) {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "MonitoredObjectLog.txt");

	int FileOpenError = fopen_s(&MyFile, FileName, "a+");
	if (0 == FileOpenError) {
		fprintf(MyFile, " 2|%s\n", aPort->FName);
		fclose(MyFile);
	}
	free(FileName);
}

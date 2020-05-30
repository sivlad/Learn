#include "CPort.h"
#include "..\StringHelper.h"


CPort::CPort() {
	FName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FName, StringHelper::DefaultBufferSize);

//	for (int i = 0; i < 3; i++) {
//		AddMonitoredParam();
//	}

}

CPort::~CPort() {
	free(FName);

	for (CMonitoredParam* LInMonitoring : FMonitoredParam) {
//		SaveMonitoredParam(LInMonitoring);
		delete(LInMonitoring);
	}

}

void CPort::AddMonitoredParam() {
	CMonitoredParam* LParam = new CMonitoredParam();
	strcpy_s(LParam->FName, StringHelper::DefaultBufferSize, "IncomTraffic");
	strcpy_s(LParam->FSNMPComand, StringHelper::DefaultBufferSize, "c:\\usr\\bin\\snmpget -v 2c -c public localhost ifInOctets.14 >> d:\\log");
	strcpy_s(LParam->FLogfileName, StringHelper::DefaultBufferSize, "localhost1_LAN interface_IncomTraffic_log.txt");
	FMonitoredParam.push_back(LParam);
}

void CPort::AddMonitoredParam(char* aName, char* aConectionString, char* aLogfileName) {
	CMonitoredParam* LParam = new CMonitoredParam();
	strcpy_s(LParam->FName, StringHelper::DefaultBufferSize, aName);
	strcpy_s(LParam->FSNMPComand, StringHelper::DefaultBufferSize, aConectionString);
	strcpy_s(LParam->FLogfileName, StringHelper::DefaultBufferSize, aLogfileName);
	FMonitoredParam.push_back(LParam);
}


void CPort::SaveMonitoredParam(CMonitoredParam* aMonitoredParam) {
	FILE* MyFile;
	char* FileName = (char*)malloc(StringHelper::DefaultBufferSize * sizeof(char));
	StringHelper::Null(FileName, StringHelper::DefaultBufferSize);
	strcpy_s(FileName, StringHelper::DefaultBufferSize, "MonitoredObjectLog.txt");

	int FileOpenError = fopen_s(&MyFile, FileName, "a+");
	if (0 == FileOpenError) {
		fprintf(MyFile, "  3|%s|%s|%s\n", aMonitoredParam->FName, aMonitoredParam->FSNMPComand, aMonitoredParam->FLogfileName);
		fclose(MyFile);
	}
	free(FileName);
}
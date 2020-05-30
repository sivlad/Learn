#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <locale.h>
#include "./ApplicationConsts.h"
#include "./StringHelper.h"
#include "./Console.h"
#include "./Environment.h"
#include "./Path.h"
#include "./Directory.h"


void OnFileFound(const char* FilePath, const char* FileName) {
	printf("  -- %s\\%s\n", FilePath, FileName);
}

int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Console::SetColor(Console::DefaultBgColor, Console::DefaultBgColor);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());
	Console::SetColor(Console::DefaultColor  , Console::DefaultBgColor);
	Console::GotoXY(0, 2);
/*
	// работа с полным путём к каталогу
	char* MyDoc = Environment::GetFolderPath(Environment::MyDocuments);
	printf("My Documents = %s \n", MyDoc);

	Path::Combine(MyDoc, ApplicationFolder);
	printf("ApplicationFolder = %s \n", MyDoc);

	if (!Directory::Exists(MyDoc) ) {
		if (!Directory::Create(MyDoc)) {
			printf("Не удалось создать каталог %s для работы приложения\n", MyDoc);
		}
	} else {
		if (!Directory::Delete(MyDoc)) {
			printf("Не удаётся удалить каталог %s \n", MyDoc);
		}
	}
	free(MyDoc);
	
	// Работа с локальным путём
	MyDoc = Environment::GetFolderPath(Environment::MyDocuments);
	Environment::SetCurrentDir(MyDoc);
	if (!Directory::Exists(ApplicationFolder)) {
		printf("dir does not exists\n");
		if (!Directory::Create(ApplicationFolder)) {
			printf("Не удалось создать каталог %s в папке %s для работы приложения\n", ApplicationFolder, MyDoc);
		}
	} else {
		printf("dir exists\n");
	}

	Environment::SetCurrentDir(ApplicationFolder);
	if (!Directory::Exists("Data")) {
		if (!Directory::Create("Data")) {
			printf("Не удалось создать каталог %s\\Data в папке %s для работы приложения\n", ApplicationFolder, MyDoc);
		}
	}
	free(MyDoc);
*/
	Directory::FindFiles("d:\\", "*.txt", &OnFileFound);

	return 0;
}
#include <iostream>
#include <Windows.h>
#include "../Application.h"

void App_OnKeyEscape(Application* Sender) {
	printf("pressed key Escape \n");
	Sender->Running = false;
}

int main() {
	Application *App = new Application();
	App->OnEscape = &App_OnKeyEscape;
	App->Run();
	delete App;
	return 0;
}

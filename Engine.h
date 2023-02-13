#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>

#include "TModel.h"

#pragma warning (disable : 4996)

class Engine
{
public:
	Engine(int, int);

	void setPixelSize(int, int);
	bool getState() const;

	void run();
	bool detectCollision(TModel, TModel);

	void addModel(TModel*);

	void render();

private:
	BOOL SetConsoleSize(int, int);

	int width;
	int height;

	HWND hWnd;
	HANDLE hConOut;
	CONSOLE_FONT_INFO fi;
	CONSOLE_SCREEN_BUFFER_INFO bi;
	CONSOLE_FONT_INFOEX cfi;
	char* screenBuffer;

	bool windowState;

	int x;
	int y;

	std::vector<TModel*> objectsTable;
};


#pragma once

#include <windows.h>


class Screen
{
private:
	static Screen *globalScreen;

public:
	static Screen *GetScreen();

private:
	Screen();
	int g_nScreenIndex;
	HANDLE g_hScreen[2];

public:
	~Screen();

	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenPrint(int x, int y, char *string);
	void SetColor(unsigned short color);
};


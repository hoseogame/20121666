#pragma once

#include <windows.h>

class G_SCREEN{
public:
	G_SCREEN();
	~G_SCREEN();

	void ScreenFlipping();
	void ScreenClear();
	void ScreenPrint(short x, short y, char *string);
	void SetColor(unsigned short color);

	CONSOLE_CURSOR_INFO cci;
	int g_nScreenIndex;
	HANDLE g_hScreen[2];

	COORD Coor;
	DWORD dw;

	DWORD dw2;
	COORD CursorPosition;
};
#include "Screen.h"

Screen::Screen()
{
	ScreenInit();
}


Screen::~Screen()
{
}

Screen *Screen::globalScreen = nullptr;

Screen *Screen::GetScreen()
{
	if (!globalScreen) {
		globalScreen = new Screen();
	}

	return globalScreen;
}


void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	g_nScreenIndex = 0;

	// 가상의 콘솔창 2개룰 만든다.
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void Screen::ScreenFlipping()
{
	Sleep(10);
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void Screen::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void Screen::ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}


void Screen::ScreenPrint(int x, int y, char *string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

// 1 ~ 15 까지 색상 설정 가능
void Screen::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}
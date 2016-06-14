#include "Football_G_SCREEN.h"

G_SCREEN::G_SCREEN()
{
	// 가상의 콘솔창 2개룰 만든다.
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	g_nScreenIndex = 0;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

G_SCREEN::~G_SCREEN()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void G_SCREEN::ScreenFlipping()
{
	Sleep(10);
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void G_SCREEN::ScreenClear()
{
	Coor = { 0, 0 };
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void G_SCREEN::ScreenPrint(short x, short y, char *string)
{
	CursorPosition = { x, y };

	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw2, NULL);
}

// 1 ~ 15 까지 색상 설정 가능
void G_SCREEN::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}
#include "Game.h"

void Game::Init() {
	gameSeletion = empty;
	globalScreen = Screen::GetScreen();

	posX = 10;
	posY = 9;
}

void Game::Update() {
	switch (gameSeletion) {
		case empty:
			while (SelectGame(&gameSeletion) == empty) {}
			break;
		case dudagi:
			dudagiGame->Init();

			while (true)
			{
				dudagiGame->Update();
				dudagiGame->Render();
			}
			break;
		case football:
			while (FootballGame->KeyHandle())
			{
				FootballGame->Update();
				FootballGame->Render();
			}
			break;
	}
}

GameType Game::SelectGame(GameType *GT) {
	globalScreen->GetScreen()->ScreenClear();

	globalScreen->GetScreen()->ScreenPrint(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	globalScreen->GetScreen()->ScreenPrint(0, 1, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 2, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 3, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 4, "┃              Two Kinds Game              ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 5, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 6, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 7, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 8, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 9, "┃              ◎ 두더지 게임              ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 10, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 11, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 12, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 13, "┃              ◎ 풋볼 게임                ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 14, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 15, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 16, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 17, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 18, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 19, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 20, "┃       w : ↑  s : ↓  선택 : Enter       ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 21, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 22, "┃                                          ┃");
	globalScreen->GetScreen()->ScreenPrint(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━┛");

	if (_kbhit()) {
		inputch = _getch();

		switch (inputch) {
		case 'W':
		case 'w':
			posY -= 4;
			break;
		case 'S':
		case 's':
			posY += 4;
			break;
		}
	}

	if (posY < 9) posY = 9;
	if (posY > 13) posY = 13;

	globalScreen->GetScreen()->ScreenPrint(posX, posY, "▷");
	//cout << cursor << endl;
	Sleep(50);
	//system("cls");

	globalScreen->GetScreen()->ScreenFlipping();

	if (_kbhit) {
		if (inputch == 13) {
			switch (posY)
			{
			case 9:
				*GT = dudagi;
				break;
			case 13:
				*GT = football;
				break;
			default:
				break;
			}
		}
	}

	return *GT;
}
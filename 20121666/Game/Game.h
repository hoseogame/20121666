#pragma once

#include "Dudagi_GameManager.h"
#include "Football_FootballManager.h"
#include "Screen.h"

typedef enum _GameType { empty, dudagi, football } GameType;

class Game {

private:
	GameType gameSeletion = empty;

	GameManager *dudagiGame = new GameManager;
	FootballManager *FootballGame = new FootballManager();

	GameType SelectGame(GameType *GT);
	Screen *globalScreen;

	char inputch;
	int posX;
	int posY;

public:
	void Init();
	void Update();
};
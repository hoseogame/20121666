#pragma once

#include <iostream>
#include <conio.h>
#include <string.h>

#include "Football_StageInfo.h"
#include "Football_Player.h"
#include "Football_Ball.h"
#include "Football_Goalpost.h"
#include "Football_Effect.h"
#include "enum.h"
#include "Screen.h"

class FootballManager {
public:
	FootballManager();
	~FootballManager();

	void Init();

	bool KeyHandle();
	void Update();
	void Render();

private:
	//ΩÃ±€≈Ê Ω∫≈©∏∞
	Screen *globalScreen = Screen::GetScreen();

	int nKey;
	int nRemain;

	GAME_STATE g_GameState;

	char* g_strPlayer;

	int g_nLength;
	int g_nGoal;
	int g_nBallCount;
	int g_nGoalBallCount;
	int g_nStage;
	int g_nIsGoal;

	clock_t g_LimitTime;
	clock_t g_GameStartTime;
	clock_t g_UpdateOldTime;
	
	StageInfo* fStageInfo[2];
	Player* fPlayer;
	Ball* fBall;
	Goalpost* fGoalpost;
	Effect* fEffect;

	void InitScreen();
	void ReadyScreen();
	void BackScreen();
	void GoalMessage(int nX, int nY);
	void SuccessScreen();
	void FailureScreen();
	void ResultScreen();
};
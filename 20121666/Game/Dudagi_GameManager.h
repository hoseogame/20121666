#pragma once

#include <iostream>
#include <conio.h>
#include <ctime>

#include "Screen.h"
#include "Dudagi_Stage.h"
#include "Dudagi_Mangchi.h"
#include "Dudagi_Dudagi.h"
#include "enum.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();
	void Update();
	void Render();

private:
	//ΩÃ±€≈Ê Ω∫≈©∏∞
	Screen *globalScreen = Screen::GetScreen();

	void InitScreen();
	void ReadyScreen();
	void SuccessScreen();
	void RunningScreen();
	void FailureScreen();
	void ResultScreen();

	void InputKey();
	int nKey;

	bool m_isMangchiAtt;

	int m_tStage;

	Stage	*m_Stage;
	Mangchi *m_Mangchi;
	Dudagi	*m_Dudagi;

	GAME_STATE	m_nGameState;

	int m_nTotalGrade;//√—¡°
	int m_nDudagiCount;
	int m_nStage;
	int m_nGrade;

	clock_t		m_GameStartTime, m_UpdateOldTime, m_RemainTime;
};


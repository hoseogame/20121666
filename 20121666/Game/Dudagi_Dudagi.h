#pragma once

#include <ctime>
#include <cstdlib>

#include "Screen.h"
#include "Dudagi_Stage.h"

typedef enum _DUDAGI_STATE { SETUP, UP, DOWN } DUDAGI_STATE;

class Dudagi
{
public:
	Dudagi();
	~Dudagi();

	void Init(Stage *_StageInfo, int _num);
	void Update(clock_t _CurTime, Stage _stage);
	void Render();

	bool IsDudagiDown(int _mangchiIndex);

	int GetnX();
	int GetnY();

private:
	Screen *globalScreen = Screen::GetScreen();

	int m_Num;

	int m_nX, m_nY;

	DUDAGI_STATE	m_nState;		// Note: �δ��� ����	
	clock_t			m_StayTime;		// Note: ���� �� ��� �ð�
	clock_t			m_OutPutTime;	// Note: ������ �� ��� �ð�
	clock_t			m_OldTime;		// Note: ���� �ð�	
};


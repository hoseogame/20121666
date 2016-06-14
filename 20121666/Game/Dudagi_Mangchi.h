#pragma once
#include <iostream>
#include <ctime>

#include "Screen.h"

class Mangchi
{
public:
	Mangchi();
	~Mangchi();

	void Init(clock_t _GameStartTime);
	void Update(int _nKey);
	void Render(int _dudaginX, int _dudaginY);

	bool GetAttack();
	int GetIndex();

	void Delay(clock_t _CurTime);

private:
	Screen *globalScreen = Screen::GetScreen();

	void AttMangchi(int x, int y);
	void MangchiReady(int x, int y);

	bool	m_nIsAttack;         // 망치 상태 
	clock_t	m_StartTime;     // 타격 상태가 시작된 시각
	clock_t	m_DelayTime;     // 타격 상태의 지연 시각
	int		m_nIndex;            // 좌표 배열에 접근하기 위한 인덱스
	int		m_nStayX, m_nStayY;    // 대기 상태일 때 좌표	
};


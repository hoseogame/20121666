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

	bool	m_nIsAttack;         // ��ġ ���� 
	clock_t	m_StartTime;     // Ÿ�� ���°� ���۵� �ð�
	clock_t	m_DelayTime;     // Ÿ�� ������ ���� �ð�
	int		m_nIndex;            // ��ǥ �迭�� �����ϱ� ���� �ε���
	int		m_nStayX, m_nStayY;    // ��� ������ �� ��ǥ	
};


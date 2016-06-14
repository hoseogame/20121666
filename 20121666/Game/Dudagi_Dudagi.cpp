#include "Dudagi_Dudagi.h"



Dudagi::Dudagi()
{
}


Dudagi::~Dudagi()
{
}

void Dudagi::Init(Stage *_StageInfo, int _num)
{
	m_Num = _num+1;
	m_StayTime		= rand() % _StageInfo->GetDownLimitTime() + 10; // Note: �ּ� 10�� �ȴ�.
	m_OldTime		= clock();
	m_nState		= SETUP;
	m_OutPutTime	= rand() % _StageInfo->GetUpLimitTime() + 10; //�ּ� 10�� �ȴ�.

	//Num�� ���� �δ��� ��ġ
	if (m_Num % 3 == 1)
	{
		m_nX = 10;
	}
	else if (m_Num % 3 == 2)
	{
		m_nX = 20;
	}
	else if (m_Num % 3 == 0)
	{
		m_nX = 30;
	}

	if (m_Num >= 1 && m_Num <= 3)
	{
		m_nY = 15;
	}
	else if (m_Num >= 4 && m_Num <= 6)
	{
		m_nY = 10;
	}
	else if (m_Num >= 7 && m_Num <= 9)
	{
		m_nY = 5;
	}
}

void Dudagi::Update(clock_t _CurTime, Stage _stage)
{
	switch (m_nState)
	{
	case SETUP:
		m_OldTime = _CurTime;
		m_OutPutTime = rand() % (int)_stage.GetUpLimitTime() + 10;
		m_StayTime = rand() % (int)_stage.GetDownLimitTime() + 10;
		m_nState = UP;
		break;
	case UP:
		if (_CurTime - m_OldTime > m_OutPutTime)
		{
			m_OldTime = _CurTime;
			m_nState = DOWN;
		}
		break;
	case DOWN:
		if (_CurTime - m_OldTime > m_StayTime)
			m_nState = SETUP;
		break;
	}
}

void Dudagi::Render()
{
	if (m_nState == UP)
		globalScreen->GetScreen()->ScreenPrint(m_nX, m_nY, "��");

	globalScreen->GetScreen()->ScreenPrint(m_nX, m_nY + 1, "��");
}


bool Dudagi::IsDudagiDown(int _mangchiIndex)
{
	if (m_nState == UP && m_Num == _mangchiIndex)
	{
		m_nState = DOWN; // �׾����� �ٿ� ���·� �ٷ� ��ȯ�� �ϵ��� �Ѵ�.
		return true;
	}

	return false;
}

int Dudagi::GetnX()
{
	return m_nX;
}

int Dudagi::GetnY()
{
	return m_nY;
}
#include "Dudagi_Mangchi.h"



Mangchi::Mangchi()
{
}


Mangchi::~Mangchi()
{
}


void Mangchi::Init(clock_t _GameStartTime)
{
	//蜂纂 蟾晦��
	m_nIsAttack = false;
	m_nIndex = 0;
	m_nStayX = 38;
	m_nStayY = 10;
	m_StartTime = 0;
	m_DelayTime = 300;
}

void Mangchi::Update(int _nKey)
{
	m_nIndex = _nKey - '1';
	m_StartTime = clock();
	m_nIsAttack = true;
}

void Mangchi::Render(int _dudaginX, int _dudaginY)
{
	if (m_nIsAttack)
		AttMangchi(_dudaginX, _dudaginY);
	else
		MangchiReady(m_nStayX, m_nStayY);
}

bool Mangchi::GetAttack()
{
	return m_nIsAttack;
}

int Mangchi::GetIndex()
{
	return m_nIndex;
}

void Mangchi::Delay(clock_t _CurTime)
{
	if (_CurTime - m_StartTime > m_DelayTime)
	{
		m_nIsAttack = false;
	}
}

void Mangchi::AttMangchi(int x, int y)
{
	globalScreen->GetScreen()->ScreenPrint(x - 4, y - 1, "≧旨收旬");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y, "↖早統早㏑㏑↖↗");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y + 1, "≧曲收旭");
}

void Mangchi::MangchiReady(int x, int y)
{
	globalScreen->GetScreen()->ScreenPrint(x - 4, y - 2, "    ↘");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y - 1, "  旨收旬");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y, "  早  早");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y + 1, "  曲收旭");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y + 2, "    ‵");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y + 3, "    ‵");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y + 4, "    ↘");
	globalScreen->GetScreen()->ScreenPrint(x - 4, y + 5, "    ↙");
}
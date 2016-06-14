#include "Dudagi_Stage.h"



Stage::Stage()
{
}


Stage::~Stage()
{
}

void Stage::Init(int _nCatchDudagi, clock_t _LimitTime, clock_t _UpLimitTime, clock_t _DownLimitTime)
{
	m_nCatchDudagi = _nCatchDudagi;
	m_LimitTime = _LimitTime;
	m_UpLimitTime = _UpLimitTime;
	m_DownLimitTime = _DownLimitTime;
}

clock_t Stage::GetUpLimitTime()
{
	return m_UpLimitTime;
}

clock_t Stage::GetDownLimitTime()
{
	return m_DownLimitTime;
}

clock_t Stage::GetLimitTime() 
{
	return m_LimitTime;
}

bool Stage::IsSuccess(int _nDudagiCount)
{
	if (_nDudagiCount >= m_nCatchDudagi)
		return true;
	else
		return false;
}

int Stage::GetnCatchDudagi()
{
	return m_nCatchDudagi;
}
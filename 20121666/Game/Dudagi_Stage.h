#pragma once

#include <ctime>

class Stage
{
public:
	Stage();
	~Stage();

	void Init(int _nCatchDudagi, clock_t _LimitTime, clock_t _UpLimitTime, clock_t _DownLimitTime);

	clock_t GetUpLimitTime();
	clock_t GetDownLimitTime();
	clock_t GetLimitTime();

	bool IsSuccess(int _nDudagiCount);

	int GetnCatchDudagi();
private:
	//StageInfo
	int m_nCatchDudagi;
	clock_t m_LimitTime;
	clock_t m_UpLimitTime;
	clock_t m_DownLimitTime;
};


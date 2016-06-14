#pragma once
#include <time.h>

class Effect
{
public:
	Effect();
	~Effect();

	void SetStartTime(clock_t i_StartTime);
	void SetStayTime(clock_t i_StayTime);

	clock_t GetStartTime();
	clock_t GetStayTime();

private:
	clock_t StartTime;
	clock_t StayTime;
};
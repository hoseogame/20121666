#include "Football_Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::SetStartTime(clock_t i_StartTime)
{
	StartTime = i_StartTime;
}
void Effect::SetStayTime(clock_t i_StayTime)
{
	StayTime = i_StayTime;
}

clock_t Effect::GetStartTime()
{
	return StartTime;
}
clock_t Effect::GetStayTime()
{
	return StayTime;
}
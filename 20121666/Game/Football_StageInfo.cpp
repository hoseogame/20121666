#include "Football_StageInfo.h"

StageInfo::StageInfo(int i_nGoalBall, clock_t i_LimitTime, int i_GoalDaeLength,
	int i_GoalDaeX, int i_GoalDaeY, clock_t i_MoveTime, int i_Dist)
{
	nGoalBall		= i_nGoalBall;
	LimitTime		= i_LimitTime;
	nGoalDaeLength	= i_GoalDaeLength;
	nGoalDaeX		= i_GoalDaeX;
	nGoalDaeY		= i_GoalDaeY;
	MoveTime		= i_MoveTime;
	nDist			= i_Dist;
}

StageInfo::~StageInfo()
{
}


int StageInfo::GetGoalBall()
{
	return nGoalBall;
}

int StageInfo::GetGoalDaeX()
{
	return nGoalDaeX;
}

int StageInfo::GetGoalDaeY()
{
	return nGoalDaeY;
}

int StageInfo::GetGoalDaeLength()
{
	return nGoalDaeLength;
}

int StageInfo::GetnDist()
{
	return nDist;
}

clock_t StageInfo::GetLimitTime()
{
	return LimitTime;
}

clock_t StageInfo::GetMoveTime()
{
	return MoveTime;
}
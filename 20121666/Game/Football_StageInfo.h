#pragma once
#include <time.h>

class StageInfo {
public:
	StageInfo(int i_nGoalBall, clock_t i_LimitTime, int i_GoalDaeLength,
		int i_GoalDaeX, int i_GoalDaeY, clock_t i_MoveTime, int i_Dist);
	~StageInfo();

	int GetGoalBall();
	int GetGoalDaeX();
	int GetGoalDaeY();
	int GetGoalDaeLength();
	int GetnDist();
	clock_t GetLimitTime();
	clock_t GetMoveTime();

private:
	int nGoalBall;			// 골인해야 할 볼의 개수 
	clock_t LimitTime;      // 제한 시간 
	int nGoalDaeLength;		// 골대 길이 
	int nGoalDaeX;			// 골대 이동 X 좌표
	int nGoalDaeY;			// 골대 이동 Y 좌표 
	clock_t MoveTime;		// 골대 이동 시간 간격
	int nDist;				// 골대 이동 거리
};
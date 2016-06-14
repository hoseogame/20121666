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
	int nGoalBall;			// �����ؾ� �� ���� ���� 
	clock_t LimitTime;      // ���� �ð� 
	int nGoalDaeLength;		// ��� ���� 
	int nGoalDaeX;			// ��� �̵� X ��ǥ
	int nGoalDaeY;			// ��� �̵� Y ��ǥ 
	clock_t MoveTime;		// ��� �̵� �ð� ����
	int nDist;				// ��� �̵� �Ÿ�
};
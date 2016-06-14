#pragma once
#include <time.h>

class Object {
public:
	Object(int i_nMoveX, int i_nMoveY, clock_t i_MoveTime, clock_t OldTime = 0);
	~Object();

	int nMoveX, nMoveY;     // 이동 좌표 
	clock_t MoveTime;    // 이동 시간 간격
	clock_t OldTime;     // 이전 이동 시각
};
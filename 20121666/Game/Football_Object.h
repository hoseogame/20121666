#pragma once
#include <time.h>

class Object {
public:
	Object(int i_nMoveX, int i_nMoveY, clock_t i_MoveTime, clock_t OldTime = 0);
	~Object();

	int nMoveX, nMoveY;     // �̵� ��ǥ 
	clock_t MoveTime;    // �̵� �ð� ����
	clock_t OldTime;     // ���� �̵� �ð�
};
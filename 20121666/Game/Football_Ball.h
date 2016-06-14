#pragma once
#include "Football_Object.h"

class Ball : public Object
{
public:
	Ball(bool i_nIsReady, int i_nMoveX, int i_nMoveY, clock_t i_MoveTime);
	~Ball();

	void SetIsReady(int i_nIsReady);
	bool GetIsReady();

private:
	bool nIsReady;        // �غ� ����(true), ������(false)
};


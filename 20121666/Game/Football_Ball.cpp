#include "Football_Ball.h"

Ball::Ball(bool i_nIsReady, int i_nMoveX, int i_nMoveY, clock_t i_MoveTime) : Object(i_nMoveX, i_nMoveY, i_MoveTime)
{
	nIsReady = i_nIsReady;
}

Ball::~Ball()
{
}

void Ball::SetIsReady(int i_nIsReady)
{
	nIsReady = i_nIsReady;
}

bool Ball::GetIsReady()
{
	return nIsReady;
}
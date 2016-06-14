#include "Football_Goalpost.h"

Goalpost::Goalpost(int i_nMoveX, int i_nMoveY, int i_nLength, int i_nDist, clock_t i_MoveTime, clock_t i_OldTime) : Object(i_nMoveX, i_nMoveY, i_MoveTime)
{
	Init(i_nMoveX, i_nMoveY, i_nLength, i_nDist, i_MoveTime, i_OldTime);
}
Goalpost::~Goalpost()
{
}
void Goalpost::Init(int i_nMoveX, int i_nMoveY, int i_nLength, int i_nDist, clock_t i_MoveTime, clock_t i_OldTime) 
{
	nMoveX = i_nMoveX;
	nMoveY = i_nMoveY;
	MoveTime = i_MoveTime;
	OldTime = i_OldTime;

	nLength = i_nLength;
	nDist = i_nDist;
}

int Goalpost::GetnLength()
{
	return nLength;
}

int Goalpost::GetnDist()
{
	return nDist;
}

int Goalpost::GetnLineX(int arrNum)
{
	return nLineX[arrNum];
}

void Goalpost::SetnLineX()
{
	for (int i = 0; i < 7; i++)
		nLineX[i] = nMoveX + (2 * (i + 1));
}

void Goalpost::SetnDist(int i_nDist)
{
	nDist = i_nDist;
}
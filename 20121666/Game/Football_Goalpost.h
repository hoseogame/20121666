#pragma once
#include "Football_Object.h"

class Goalpost : public Object 
{
public:
	Goalpost(int i_nMoveX, int i_nMoveY, int i_nLength, int i_nDist, clock_t i_MoveTime, clock_t i_OldTime);
	~Goalpost();

	void Init(int i_nMoveX, int i_nMoveY, int i_nLength, int i_nDist, clock_t i_MoveTime, clock_t i_OldTime);

	int GetnLength();
	int GetnDist();
	int GetnLineX(int arrNum);

	void SetnLineX();
	void SetnDist(int i_nDist);

private:
	int nLength;			// ��� ����	
	int nLineX[7];			// ���� ���� x ��ǥ (7��)
	int	nDist;				// �̵� �Ÿ�
};
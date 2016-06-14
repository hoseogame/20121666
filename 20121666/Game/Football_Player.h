#pragma once

class Player
{
public:
	Player(int i_nCenterX, int i_nCenterY, int i_nMoveX, int i_nMoveY);
	~Player();

	void SetnX(int i_nX);
	int GetnX();

	int nCenterX, nCenterY;
	int nMoveX, nMoveY;

private:
	int nX;
};
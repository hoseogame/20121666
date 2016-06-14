#include "Football_Player.h"

Player::Player(int i_nCenterX, int i_nCenterY, int i_nMoveX, int i_nMoveY) 
			: nCenterX(i_nCenterX), nCenterY(i_nCenterY), nMoveX(i_nMoveX), nMoveY(i_nMoveY)
{

}
Player::~Player()
{
}

void Player::SetnX(int i_nX) 
{
	nX = i_nX;
}
int Player::GetnX()
{
	return nX;
}
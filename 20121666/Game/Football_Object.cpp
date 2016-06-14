#include "Football_Object.h"

Object::Object(int i_nMoveX, int i_nMoveY, clock_t i_MoveTime, clock_t i_OldTime)
			: nMoveX(i_nMoveX), nMoveY(i_nMoveY), MoveTime(i_MoveTime), OldTime(i_OldTime)
{
}
Object::~Object()
{
}
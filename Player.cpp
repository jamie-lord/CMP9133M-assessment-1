#include"player.h"

void player::Reset(void)
{
	if (index == 0)
	{
		isMyTurn = true;
	}
	else
	{
		isMyTurn = false;
	}

	score = 0;
}
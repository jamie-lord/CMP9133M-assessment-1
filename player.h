#pragma once

class player
{
	static int playerIndex;
private:
	bool isMyTurn;
	int	score;
	int index;

public:
	player()
	{
		Reset();
	}

	void Reset(void);

};
#pragma once

class player
{
	static int playerIndex;
private:
	int	score;
	int index;

public:
	player()
	{
		Reset();
	}

	void Reset(void);

};
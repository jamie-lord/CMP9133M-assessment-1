#pragma once

enum PlayerColours { PINK, GREEN };

class player
{
	static int playerIndexCnt;
public:
	int	score;
	int index;
	PlayerColours colour;

	player()
	{
		index = playerIndexCnt++;
		if (index == 0)
		{
			colour = PINK;
		}
		else {
			colour = GREEN;
		}

		Reset();
	}

	void Reset(void);

};
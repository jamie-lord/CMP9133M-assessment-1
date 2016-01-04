#pragma once

#include"ball.h"
#include"cushion.h"
#include"particleSystem.h"
#include"pocket.h"
#include"player.h"

const float TABLE_X = 0.6;
const float TABLE_Z = 1.2;
const float TABLE_Y = 0.1;

const int NUM_CUSHIONS = 4;
const int NUM_POCKETS = 6;
const int NUM_PLAYERS = 2;

class table
{
public:
	int currentActivePlayer = 0;
	ball balls[NUM_BALLS];
	cushion cushions[NUM_CUSHIONS];
	pocket pockets[NUM_POCKETS];
	particleSet parts;
	player players[NUM_PLAYERS];
	bool changePlayer = false;

	void SetupCushions(void);
	void Update(int ms);
	bool AnyBallsMoving(void) const;
};

extern table gTable;
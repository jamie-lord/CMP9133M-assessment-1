#pragma once

#include"ball.h"
#include"cushion.h"
#include"particleSystem.h"

const float TABLE_X = 0.6;
const float TABLE_Z = 1.2;
const float TABLE_Y = 0.1;

const int NUM_CUSHIONS = 4;

class table
{
public:
	ball balls[NUM_BALLS];
	cushion cushions[NUM_CUSHIONS];
	particleSet parts;

	void SetupCushions(void);
	void Update(int ms);
	bool AnyBallsMoving(void) const;
};

extern table gTable;
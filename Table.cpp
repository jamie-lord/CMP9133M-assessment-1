#include"table.h"
#include <math.h>

table gTable;

void table::SetupCushions(void)
{
	cushions[0].vertices[0](0) = -TABLE_X;
	cushions[0].vertices[0](1) = -TABLE_Z;
	cushions[0].vertices[1](0) = -TABLE_X;
	cushions[0].vertices[1](1) = TABLE_Z;

	cushions[1].vertices[0](0) = -TABLE_X;
	cushions[1].vertices[0](1) = TABLE_Z;
	cushions[1].vertices[1](0) = TABLE_X;
	cushions[1].vertices[1](1) = TABLE_Z;

	cushions[2].vertices[0](0) = TABLE_X;
	cushions[2].vertices[0](1) = TABLE_Z;
	cushions[2].vertices[1](0) = TABLE_X;
	cushions[2].vertices[1](1) = -TABLE_Z;

	cushions[3].vertices[0](0) = TABLE_X;
	cushions[3].vertices[0](1) = -TABLE_Z;
	cushions[3].vertices[1](0) = -TABLE_X;
	cushions[3].vertices[1](1) = -TABLE_Z;

	for (int i = 0; i<NUM_CUSHIONS; i++)
	{
		cushions[i].MakeCentre();
		cushions[i].MakeNormal();
	}
}

void table::Update(int ms)
{
	//check for collisions for each ball
	for (int i = 0; i < NUM_BALLS; i++)
	{
		if (isnan(balls[i].velocity(0)) || isnan(balls[i].velocity(1)))
		{
			balls[i].velocity = 0.0;
		}
		if (!balls[i].inPocket)
		{
			for (int j = 0; j < NUM_POCKETS; j++)
			{
				balls[i].DoPocketCollison(pockets[j]);
			}

			for (int j = 0; j < NUM_CUSHIONS; j++)
			{
				balls[i].DoPlaneCollision(cushions[j]);
			}

			for (int j = (i + 1); j < NUM_BALLS; j++)
			{
				balls[i].DoBallCollision(balls[j]);
			}
		}
	}

	//update all balls
	for (int i = 0; i < NUM_BALLS; i++) {
		if(!balls[i].inPocket)
			balls[i].Update(ms);
	}

	//update particles
	parts.update(ms);

	//reset cue ball if pocketed
	if (balls[0].inPocket && !gTable.AnyBallsMoving())
		balls[0].Reset();
}

bool table::AnyBallsMoving(void) const
{
	//return true if any ball has a non-zero velocity
	for (int i = 0; i<NUM_BALLS; i++)
	{
		if (balls[i].velocity(0) != 0.0) return true;
		if (balls[i].velocity(1) != 0.0) return true;
	}
	return false;
}

void table::ResetTable()
{
	// reset those balls
	for (int i = 0; i<NUM_BALLS; i++)
	{
		balls[i].Reset();
	}
	// reset current player
	currentActivePlayer = 0;
	// reset all player's scores
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		players[i].score = 0;
	}
	// reset balls on table count
	ballsOnTable = NUM_BALLS;
}
#include"table.h"

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

	/*cushions[4].vertices[0](0) = TABLE_X - 0.3;
	cushions[4].vertices[0](1) = -TABLE_Z;
	cushions[4].vertices[1](0) = -TABLE_X;
	cushions[4].vertices[1](1) = -TABLE_Z;*/

	for (int i = 0; i<NUM_CUSHIONS; i++)
	{
		cushions[i].MakeCentre();
		cushions[i].MakeNormal();
	}
}

void table::Update(int ms)
{
	//check for collisions for each ball
	for (int i = 0; i<NUM_BALLS; i++)
	{
		for (int j = 0; j<NUM_POCKETS; j++)
		{
			balls[i].DoPocketCollison(pockets[j]);
		}

		for (int j = 0; j<NUM_CUSHIONS; j++)
		{
			balls[i].DoPlaneCollision(cushions[j]);
		}

		for (int j = (i + 1); j<NUM_BALLS; j++)
		{
			balls[i].DoBallCollision(balls[j]);
		}
	}

	//update all balls
	for (int i = 0; i<NUM_BALLS; i++) balls[i].Update(ms);

	//update particles
	parts.update(ms);

	//make some new particles
	//vec3 pos(0.0,BALL_RADIUS,0.0);
	//parts.AddParticle(pos);
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
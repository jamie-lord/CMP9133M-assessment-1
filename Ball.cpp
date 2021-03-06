#include<stdlib.h>
#include <iostream>
#include"table.h"
#include"ball.h"

using namespace std;

const float gCoeffRestitution = 0.5;
float gCoeffFriction = 0.03;
float gGravityAccn = 9.8;

const float quarterTableLength = (2 * (TABLE_Z)) / 4;

int ball::ballIndexCnt = 0;

void ball::Reset(void)
{
	//set velocity to zero
	velocity = 0.0;

	//set onto table
	inPocket = false;

	//reset the cue ball
	if (index == 0)
	{
		position(0) = 0.0;
		position(1) = quarterTableLength;
		cout << "RESET CUE BALL" << endl;
		return;
	}
	else {

		//setup ball position
		static const float sep = (BALL_RADIUS*3.0f);
		static const float rowSep = (BALL_RADIUS*2.5f);
		int row = 1;
		int rowIndex = index;
		while (rowIndex > row)
		{
			rowIndex -= row;
			row++;
		}
		position(0) = (((row - 1)*sep) / 2.0f) - (sep*(row - rowIndex));
		position(1) = -((rowSep * (row - 1)) + quarterTableLength);
	}
}

void ball::ApplyImpulse(vec2 imp)
{
	velocity = imp;
}

void ball::ApplyFrictionForce(int ms)
{
	if (velocity.Magnitude() <= 0.0) return;

	//accelaration is opposite to direction of motion
	vec2 accelaration = -velocity.Normalised();
	//friction force = constant * mg
	//F=Ma, so accelaration = force/mass = constant*g
	accelaration *= (gCoeffFriction * gGravityAccn);
	//integrate velocity : find change in velocity
	vec2 velocityChange = ((accelaration * ms) / 1000.0f);
	//cap magnitude of change in velocity to remove integration errors
	if (velocityChange.Magnitude() > velocity.Magnitude()) velocity = 0.0;
	else velocity += velocityChange;
}

void ball::DoBallCollision(ball &b)
{
	if (HasHitBall(b)) HitBall(b);
}

void ball::DoPlaneCollision(const cushion &b)
{
	if (HasHitPlane(b)) HitPlane(b);
}

void ball::DoPocketCollison(const pocket &p)
{
	if (HasHitPocket(p)) HitPocket(p);
}

void ball::Update(int ms)
{
	//apply friction
	ApplyFrictionForce(ms);
	//integrate position
	position += ((velocity * ms) / 1000.0f);
	//set small velocities to zero
	if (velocity.Magnitude() < SMALL_VELOCITY) velocity = 0.0;
}

bool ball::HasHitPlane(const cushion &c) const
{
	//if moving away from plane, cannot hit
	if (velocity.Dot(c.normal) >= 0.0) return false;

	//if in front of plane, then have not hit
	vec2 relPos = position - c.vertices[0];
	double sep = relPos.Dot(c.normal);
	if (sep > radius) return false;
	return true;
}

bool ball::HasHitBall(const ball &b) const
{
	//work out relative position of ball from other ball,
	//distance between balls
	//and relative velocity
	vec2 relPosn = position - b.position;
	float dist = (float)relPosn.Magnitude();
	vec2 relPosnNorm = relPosn.Normalised();
	vec2 relVelocity = velocity - b.velocity;

	//if moving apart, cannot have hit
	if (relVelocity.Dot(relPosnNorm) >= 0.0) return false;
	//if distnce is more than sum of radii, have not hit
	if (dist > (radius + b.radius)) return false;
	return true;
}

bool ball::HasHitPocket(const pocket &p) const
{
	//work out relative position of ball from pocket,
	//distance between ball and pocket
	//and relative velocity
	vec2 relPosn = position - p.position;
	float dist = (float)relPosn.Magnitude();
	vec2 relPosnNorm = relPosn.Normalised();
	//vec2 relVelocity = velocity - p.velocity;

	//if moving apart, cannot have hit
	//if (relVelocity.Dot(relPosnNorm) >= 0.0) return false;
	//if distnce is more than sum of radii, have not hit
	if (dist > (radius + p.radius)) return false;
	return true;
}

void ball::HitPlane(const cushion &c)
{
	cout << "Ball " << index << " has hit a plane" << endl;
	//reverse velocity component perpendicular to plane  
	double comp = velocity.Dot(c.normal) * (1.0 + gCoeffRestitution);
	vec2 delta = -(c.normal * comp);
	velocity += delta;

	//make some particles
	int n = (rand() % 4) + 3;
	vec3 pos(position(0), radius / 2.0, position(1));
	vec3 oset(c.normal(0), 0.0, c.normal(1));
	pos += (oset*radius);
	for (int i = 0; i < n; i++)
	{
		gTable.parts.AddParticle(pos);
	}
}

void ball::HitBall(ball &b)
{
	cout << "Ball " << index << " has hit ball " << b.index << endl;

	//find direction from other ball to this ball
	vec2 relDir = (position - b.position).Normalised();

	//split velocities into 2 parts:  one component perpendicular, and one parallel to 
	//the collision plane, for both balls
	//(NB the collision plane is defined by the point of contact and the contact normal)
	float perpV = (float)velocity.Dot(relDir);
	float perpV2 = (float)b.velocity.Dot(relDir);
	vec2 parallelV = velocity - (relDir*perpV);
	vec2 parallelV2 = b.velocity - (relDir*perpV2);

	//Calculate new perpendicluar components:
	//v1 = (2*m2 / m1+m2)*u2 + ((m1 - m2)/(m1+m2))*u1;
	//v2 = (2*m1 / m1+m2)*u1 + ((m2 - m1)/(m1+m2))*u2;
	float sumMass = mass + b.mass;
	float perpVNew = (float)((perpV*(mass - b.mass)) / sumMass) + (float)((perpV2*(2.0*b.mass)) / sumMass);
	float perpVNew2 = (float)((perpV2*(b.mass - mass)) / sumMass) + (float)((perpV*(2.0*mass)) / sumMass);

	//find new velocities by adding unchanged parallel component to new perpendicluar component
	velocity = parallelV + (relDir*perpVNew);
	b.velocity = parallelV2 + (relDir*perpVNew2);


	//make some particles
	int n = (rand() % 5) + 5;
	vec3 pos(position(0), radius / 2.0, position(1));
	vec3 oset(relDir(0), 0.0, relDir(1));
	pos += (oset*radius);
	for (int i = 0; i < n; i++)
	{
		gTable.parts.AddParticle(pos);
	}
}

void ball::HitPocket(const pocket &p)
{
	cout << "Ball " << index << " has entered pocket " << p.index << endl;

	inPocket = true;
	velocity = 0.0;
	position(0) = 10.0;
	position(1) = 10.0;

	// potted the cue ball!
	if (index == 0)
	{
		// deduct a point for potting the cue ball - silly player is silly
		gTable.players[gTable.currentActivePlayer].score--;
	}
	// black ball... more points!
	else if (index == 5)
	{
		gTable.players[gTable.currentActivePlayer].score = gTable.players[gTable.currentActivePlayer].score + 2;

		// decrement balls on table count
		gTable.ballsOnTable--;
	}
	else
	{
		gTable.players[gTable.currentActivePlayer].score++;

		// decrement balls on table count
		gTable.ballsOnTable--;
	}

	cout << "Player " << gTable.currentActivePlayer << " potted ball " << index << " in pocket " << p.index << ". Their current score is " << gTable.players[gTable.currentActivePlayer].score << endl;

	// change to the other player
	gTable.changePlayer = true;

	// check to see if the game is over...
	if (gTable.ballsOnTable == 1)
	{
		// thank god! the game is finally over, that probably took >9000 years
		cout << "GAME OVER! Final score..." << endl;
		int topScore = 99;
		int winner = 99;
		for (int i = 0; i < NUM_PLAYERS; i++)
		{
			cout << "Player " << i << " scored " << gTable.players[i].score << endl;
			if (topScore == 99)
			{
				topScore = gTable.players[i].score;
				winner = i;
			}
			else if (gTable.players[i].score > topScore)
			{
				topScore = gTable.players[i].score;
				winner = i;
			}
		}
		// better say who's one...
		cout << "THE WINNER IS... Player " << winner << "!" << endl;
		gTable.ResetTable();
	}
}

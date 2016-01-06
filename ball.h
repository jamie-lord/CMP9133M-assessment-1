#pragma once

#include"vecmath.h"
#include"cushion.h"
#include"pocket.h"

const float BALL_RADIUS = 0.022;
const float BALL_MASS = 0.1;

const int NUM_BALLS = 16;
const float SMALL_VELOCITY = 0.1;

const int SIM_UPDATE_MS = 10;

enum BallColours { WHITE, RED, BLACK, YELLOW };

class ball
{
	static int ballIndexCnt;
public:
	vec2	position;
	vec2	velocity;
	float	radius;
	float	mass;
	int		index;
	bool inPocket;
	BallColours colour;

	ball() : position(0.0), velocity(0.0), radius(BALL_RADIUS), mass(BALL_MASS), inPocket(false)
	{
		index = ballIndexCnt;
		ballIndexCnt++;
		if (
			index == 3 ||
			index == 4 ||
			index == 8 ||
			index == 10 ||
			index == 11 ||
			index == 12 ||
			index == 14
			)
		{
			colour = YELLOW;
		}
		else if (
			
			index == 1 ||
			index == 2 ||
			index == 6 ||
			index == 7 ||
			index == 9 ||
			index == 13 ||
			index == 15
			)
		{
			colour = RED;
		}
		else if (index == 5)
		{
			colour = BLACK;
		}
		else if (index == 0)
		{
			colour = WHITE;
		}
		Reset();
	}

	void Reset(void);
	void ApplyImpulse(vec2 imp);
	void ApplyFrictionForce(int ms);
	void DoPlaneCollision(const cushion &c);
	void DoBallCollision(ball &b);
	void DoPocketCollison(const pocket &p);
	void Update(int ms);

	bool HasHitPlane(const cushion &c) const;
	bool HasHitBall(const ball &b) const;
	bool HasHitPocket(const pocket &p) const;

	void HitPlane(const cushion &c);
	void HitBall(ball &b);
	void HitPocket(const pocket &p);
};
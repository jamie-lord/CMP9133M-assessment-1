#pragma once

#include"vecmath.h"
#include"cushion.h"
#include"pocket.h"

const float BALL_RADIUS = 0.022;
const float BALL_MASS = 0.1;

const int NUM_BALLS = 16;
const float SMALL_VELOCITY = 0.01;

const int SIM_UPDATE_MS = 10;

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

	ball() : position(0.0), velocity(0.0), radius(BALL_RADIUS), mass(BALL_MASS), inPocket(false)
	{
		index = ballIndexCnt++;
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
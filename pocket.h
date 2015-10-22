#pragma once

#include"vecmath.h"

const float POCKET_RADIUS = 0.08;

class pocket
{
private:
	static int pocketIndexCnt;
public:
	int index;
	vec2 position;
	float radius;

	pocket() : position(0.0), radius(POCKET_RADIUS)
	{
		index = pocketIndexCnt++;
		Initialise();
	}

	void Initialise(void);
};
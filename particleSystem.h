#pragma once

#include"vecmath.h"

const int MAX_PARTICLES = 200;

class particle
{
public:
	vec3 position;
	vec3 velocity;

	particle() { position = 0; velocity = 0; }
	void update(int ms);
};

class particleSet
{
public:
	particle *particles[MAX_PARTICLES];
	int numberOfActiveParticles;

	particleSet()
	{
		for (int i = 0; i<MAX_PARTICLES; i++) particles[i] = 0;
		numberOfActiveParticles = 0;
	}

	~particleSet()
	{
		for (int i = 0; i<numberOfActiveParticles; i++)
		{
			if (particles[i]) delete particles[i];
		}
	}

	void AddParticle(const vec3 &pos);
	void update(int ms);
};
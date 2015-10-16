#include<stdlib.h>
#include"particleSystem.h"

void particle::update(int ms)
{
	position += (velocity*ms) / 1000.0;
	velocity(1) -= (4.0*ms) / 1000.0; //(9.8*ms)/1000.0;
}

void particleSet::AddParticle(const vec3 &pos)
{
	if (numberOfActiveParticles >= MAX_PARTICLES) return;
	particles[numberOfActiveParticles] = new particle;
	particles[numberOfActiveParticles]->position = pos;

	particles[numberOfActiveParticles]->velocity(0) = ((rand() % 200) - 100) / 200.0;
	particles[numberOfActiveParticles]->velocity(2) = ((rand() % 200) - 100) / 200.0;
	particles[numberOfActiveParticles]->velocity(1) = 2.0*((rand() % 100) / 100.0);

	numberOfActiveParticles++;
}

void particleSet::update(int ms)
{
	int i = 0;
	while (i<numberOfActiveParticles)
	{
		particles[i]->update(ms);
		if ((particles[i]->position(1) < 0.0) && (particles[i]->velocity(1)<0.0))
		{
			delete particles[i];
			particles[i] = particles[numberOfActiveParticles - 1];
			numberOfActiveParticles--;
		}
		else i++;
	}
}
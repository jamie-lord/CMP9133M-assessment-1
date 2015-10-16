#include"cushion.h"

void cushion::MakeNormal(void)
{
	//can do this in 2d
	vec2 temp = vertices[1] - vertices[0];
	normal(0) = temp(1);
	normal(1) = -temp(0);
	normal.Normalise();
}

void cushion::MakeCentre(void)
{
	centre = vertices[0];
	centre += vertices[1];
	centre /= 2.0;
}
#include "fuzzy.h"
/*
Fuzzy::Fuzzy()
{
	left = 0.0f;
	midLeft = 0.0f;
	midRight = 0.0f;
	right = 0.0f;
};

Fuzzy::~Fuzzy(){};

void Fuzzy::setInterval(float l, float ml, float mr, float r)
{
	left = l;
	midLeft = ml;
	midRight = mr;
	right = r;
}

float Fuzzy::getValue(float t)
{
	if(t <= left)
	   return 1.0f;
	else if(t < midLeft)
		return (midLeft - t)/(midLeft-left);
	else if(t <= midRight)
		return 0.0f;
	else if(t < right)
		return (t-midRight)/(right-midRight);
	else
		return 1.0f;
}
*/

Fuzzy::Fuzzy()
{
	left = 0.0f;
	right = 0.0f;
};

Fuzzy::~Fuzzy(){};

void Fuzzy::setInterval(float l, float r)
{
	left = l;
	right = r;
}

float Fuzzy::getValue(float t)
{
	if(t <= left)
	   return 0.0f;
	else if(t < right)
		return (t-left)/(right-left);
	else
		return 1.0f;
}


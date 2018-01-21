#include <iostream>
#include <cmath>
#include <cstring>

class Fuzzy
{
public:
	float left, midLeft, midRight, right;

	Fuzzy(){};
	~Fuzzy(){};

	void setInterval(float l, float ml, float mr, float r);

	//bool isDotInInterval(float t);

	float getValue(float t);
};

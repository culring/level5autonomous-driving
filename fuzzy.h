#include <iostream>
#include <cmath>

#ifndef LEVEL5AUTONOMOUS_DRIVING_FUZZY_H
#define LEVEL5AUTONOMOUS_DRIVING_FUZZY_H

#include <vector>
#include <SFML/System/Vector2.hpp>
/*
class Fuzzy
{
public:
	std::vector<sf::Vector2i> segmentsPositions;
	std::vector<int> directions;
	float left, midLeft, midRight, right;

	Fuzzy();
	Fuzzy(std::vector<sf::Vector2i> segs, std::vector<int> dirs);
	~Fuzzy();

	void setInterval(float l, float ml, float mr, float r);

	//bool isDotInInterval(float t);

	float getValue(float t);
};
*/

class Fuzzy
{
public:
	std::vector<sf::Vector2i> segmentsPositions;
	std::vector<int> directions;
	float left, right;

	Fuzzy();
	Fuzzy(std::vector<sf::Vector2i> segs, std::vector<int> dirs);
	~Fuzzy();

	void setInterval(float l, float r);

	//bool isDotInInterval(float t);

	float getValue(float t);
};

#endif

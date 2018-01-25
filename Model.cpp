#include "Model.h"

/* Car */

Car::Car()
{
	x = 0.0f;
	y = 0.0f;
	dir = 0.0f;
	
	speed = 0.0f;
	turn = 0.0f;
}

Car::~Car() {}

void Car::turnLeft()
{
//	if (turn >= -30.0f)
//		turn = turn - 0.2f;
	if (turn >= -30.0f)
		turn = turn - 1.0f;
}

void Car::turnRight()
{
//	if (turn <= 30.0f)
//		turn = turn + 0.2f;	
	if (turn <= 30.0f)
		turn = turn + 1.0f;
}

void Car::stabilize()
{
	float rate = 10.0f;
	
	if (turn > 0.0f)
	{
		if (turn > rate)
			turn = turn - rate;
		else
			turn = 0.0f;
	}
	else if (turn < 0.0f)
	{
		if (turn < -rate)
			turn = turn + rate;
		else
			turn = 0.0f;
	}

	//turn = 0.0f;

	if(speed > 0.0f) {
		//speed -= 0.1f;
	}
}
	
void Car::accel()
{
	float rate = 0.5f;
	
	if (speed < 5.0f - rate)
		speed = speed + 0.1f;
	else
		speed = 5.0f;
}

void Car::slow()
{
	float rate = 0.05f;
	
	if (speed > rate)
		speed = speed - rate;
	else
		speed = 0.0f;
}

void Car::update()
{
	float turnRad = turn * M_PI / (180.0f * 1.0f);

	dir = dir + turn / 1.0f;

	float dirRad = dir * M_PI / 180.0f;

	float r = speed / cos(turnRad);

	x = x + r*cos(dirRad);
	y = y + r*sin(dirRad);
	turn = 0.0f;
}

/* Segment */

Segment::Segment()
{
	x = 0;
	y = 0;
	dir = 0;
	segType = 0;
	rad = 0.0f;
}

Segment::Segment(float posX, float posY, float faceDir, int segmentType, float rads)
{
	x = posX;
	y = posY;
	dir = faceDir;
	segType = segmentType;
	rad = rads;
}

Segment::~Segment() {}

void Segment::setSegment(float posX, float posY, float faceDir, int segmentType, float rads)
{
	x = posX;
	y = posY;
	dir = faceDir;
	segType = segmentType;
	rad = rads;
}


/* Track */

Track::Track()
{
	k = 0;
	segList = new Segment[TRACK_SIZE];
}

Track::~Track()
{
	delete[] segList;
}

void Track::update(float posX, float posY, float faceDir, int segmentType, float rads)
{
	segList[k].setSegment(posX, posY, faceDir, segmentType, rads);

	k = ++k % TRACK_SIZE;
}


/* Race */

Race::Race() : map(nullptr), vehicle(nullptr) {}

Race::~Race() {}

void Race::playerMode() {
	vehicle = new Car();
	map = new Track();
}

void Race::aiMode(std::vector<sf::Vector2i> segs, std::vector<int> dirs) {
	vehicle = new Car();
	map = new Track();
	fuzzySetLeft = new Fuzzy();
	fuzzySetRight = new Fuzzy();
	fuzzySetSpeedForTurn = new Fuzzy();
	fuzzySetSpeedForStraight = new Fuzzy();

	fuzzySetLeft->setInterval(0.0f, 30.0f);
	fuzzySetRight->setInterval(0.0f, 30.0f);
	//fuzzySetSpeedForTurn->setInterval(-500.0f, -450.0f, -150.0f, 800.0f);
	//fuzzySetSpeedForStraight->setInterval(-500.0f, -450.0f, -50.0f, 600.0f);
	segmentsPositions = segs;
	directions = dirs;
}

void Race::endGame() {
	delete vehicle;
	delete map;
}

void Race::endAIMode() {
	delete fuzzySetLeft;
	delete fuzzySetRight;
	delete fuzzySetSpeedForTurn;
	delete fuzzySetSpeedForStraight;
	endGame();
}

Segment* Race::getMap()
{
	return map->segList;		// ?
}

float Race::getCarX()
{
	return vehicle->x;
}

float Race::getCarY()
{
	return vehicle->y;
}

float Race::getCarDir()
{
	return vehicle->dir;
}

float Race::getCarSpeed()
{
	return vehicle->speed;
}

float Race::getCarTurn()
{
	return vehicle->turn;
}

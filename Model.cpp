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

bool Race::getSideOfPointRelativeToLineSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	// calculate determinant of
	// | p.x p.y 1 | 
	// | q.x q.y 1 |
	// | r.x r.y 1 |
	// to determine side
	return ((p.x*(q.y - r.y)) - (p.y*(q.x - r.x)) + (q.x*r.y - q.y *r.x) < 0);
}

bool Race::getSideOfVectorRelativeToVector(sf::Vector2f vectorA, sf::Vector2f vectorB)
{
	return getSideOfPointRelativeToLineSegment({ 0, 0 }, vectorA, vectorB);
}

sf::Vector2f Race::getPreviousCenter()
{
	return m_segmentsPositions[currentSegmentIndex - 1];
}

sf::Vector2f Race::getCurrentCenter()
{
	return m_segmentsPositions[currentSegmentIndex];
}

sf::Vector2f Race::getNextCenter()
{
	return m_segmentsPositions[currentSegmentIndex + 1];
}

float Race::getDotProduct(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

float Race::getVectorLength(sf::Vector2f a)
{
	return sqrt((a.x * a.x + a.y * a.y));
}

sf::Vector2f Race::getVectorFromAngle(float angle)
{
	// convert angle counted in clockwise
	// system to anti-clockwise one
	angle = 360 - angle;
	// convert to radians
	angle *= (M_PI / 180.f);
	return{ cos(angle), sin(angle) };
}

sf::Vector2f Race::getTrackVector()
{
	return getCurrentCenter() - getPreviousCenter();
}

/* Race */

Race::Race() : map(nullptr), vehicle(nullptr) {}

Race::~Race() {}

void Race::setSegmentsPositions(std::vector<sf::Vector2f> segmentsPositions)
{
	m_segmentsPositions = segmentsPositions;
}

void Race::playerMode() {
	vehicle = new Car();
	map = new Track();
}

void Race::aiMode(std::vector<sf::Vector2f> segs, std::vector<int> dirs) {
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
	m_segmentsPositions = segs;
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

sf::Vector2f Race::getCarPosition()
{
	return{ getCarX(), getCarY() };
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

float Race::getCarToTrackDistance()
{
	const sf::Vector2f previousCenter = getPreviousCenter(),
		currentCenter = getCurrentCenter();
	sf::Vector2f currentCarPosition = getCarPosition();

	float multiplier = (getCurrentCarSide()) ? -1 : 1;
	// horizontal segment
	if(previousCenter.y == currentCenter.y)
	{
		return multiplier*abs(currentCarPosition.y - previousCenter.y);
	}
	// vertical segment
	return multiplier*(currentCarPosition.x - previousCenter.x);
}

bool Race::getCurrentCarSide()
{
	sf::Vector2f previousCenter = getPreviousCenter(),
		currentCenter = getCurrentCenter(),
		carPosition = getCarPosition();

	// horizontal
	if(previousCenter.y == currentCenter.y)
	{
		float y = previousCenter.y;
		// left to right
		if(currentCenter.x > previousCenter.x)
		{
			return carPosition.y > y;
		}
		// right to left
		else
		{
			return carPosition.y < y;
		}
	}
	// vertical
	else
	{
		float x = previousCenter.x;
		// up
		if(currentCenter.y < previousCenter.y)
		{
			return carPosition.x > x;
		}
		// down
		else
		{
			return carPosition.x < x;
		}
	}
}

float Race::getCarDirectionToTrackAngle()
{
	sf::Vector2f trackVector = getTrackVector();
	sf::Vector2f carDirectionVector = getVectorFromAngle(getCarDir());
	// car direction is oriented differently
	// than track vector
	carDirectionVector.y *= -1;
	float cosine = getDotProduct(trackVector, carDirectionVector) / 
		(getVectorLength(trackVector)*getVectorLength(carDirectionVector));
	// angle in bounds [0; pi]
	float angle = acos(cosine);
	// if car direction vector lies
	// on the left of track vector
	// that means angle should be negative
	if(!getSideOfVectorRelativeToVector(trackVector, carDirectionVector))
	{
		angle *= -1;
	}
	return angle;
}

float Race::getCarToTrackAngle()
{
	sf::Vector2f trackVector = getTrackVector();
	sf::Vector2f carVector = getCarPosition() - getPreviousCenter();
	return getSideOfVectorRelativeToVector(trackVector, carVector);
}

void Race::updateSegmentIndex()
{
	sf::Vector2f carPosition = { getCarX(), getCarY() },
		nextCenter = getNextCenter();
	sf::Vector2f carToCenter = nextCenter - carPosition;
	float carDistanceToCenter = sqrt((carToCenter.x*carToCenter.x)+(carToCenter.y*carToCenter.y));
	// if near enough jump to next segment
//	if(carDistanceToCenter <= 152.85f*2)
	if(carDistanceToCenter <= 160.0f*2)
	{
		++currentSegmentIndex;
	}
	std::cout << currentSegmentIndex << std::endl;
}

unsigned Race::getCurrentSegmentIndex()
{
	return currentSegmentIndex;
}
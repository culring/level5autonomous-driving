#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif
#include "ViewTrack.h"

#ifndef LEVEL5AUTONOMOUS_DRIVING_MODEL_H
#define LEVEL5AUTONOMOUS_DRIVING_MODEL_H

#include <vector>
#include "fuzzy.h"
#include <SFML/System/Vector2.hpp>

#define TRACK_SIZE 16

class Car
{
public:
	float x, y, dir;			// car's current position and direction it's facing
	float speed;
	float turn;					// negative values for turn to the left, positive for turn to the right
	
	Car();
	~Car();
	
	void turnLeft();
	void turnRight();
	void stabilize();
	
	void accel();
	void slow();
	
	void update();
};


class Segment
{
public:
	float x, y, dir;
	int segType;
	
	float rad;					// turn degree (0 for straight segments)
	
	Segment();
	Segment(float posX, float posY, float faceDir, int segmentType, float rads);
	~Segment();
	
	void setSegment(float posX, float posY, float faceDir, int segmentType, float rads);
};


class Track
{
public:
	//std::vector<sf>
	Segment *segList;			// current track
	int k;
	
	Track();
	~Track();
	
	void update(float posX, float posY, float faceDir, int segmentType, float rads);				// replace old segments with new ones
};


class Race
{
	// false - point lies on the left
	// true - point lies on the right
	bool getSideOfPointRelativeToLineSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
	bool getSideOfVectorRelativeToVector(sf::Vector2f vectorA, sf::Vector2f vectorB);
	// get specific centers of track
	sf::Vector2f getPreviousCenter();
	sf::Vector2f getCurrentCenter();
	sf::Vector2f getNextCenter();
	// vector operations
	float getDotProduct(sf::Vector2f a, sf::Vector2f b);
	float getVectorLength(sf::Vector2f a);
	// get angle [0, 360) and output normalized
	// vector which is rotated by this angle
	// vector [1, 0]
	sf::Vector2f getVectorFromAngle(float angle);
	// get track vector
	sf::Vector2f getTrackVector();

public:
	Car *vehicle;
	Track *map;

	//	Fuzzy *fuzzySetTurn;
	Fuzzy *fuzzySetSpeedForTurn;
	Fuzzy *fuzzySetSpeedForStraight;

	Fuzzy *fuzzySetLeft;
	Fuzzy *fuzzySetRight;

	std::vector<sf::Vector2f> m_segmentsPositions;
	std::vector<int> directions;

	// used to calculate distance from track axis
	unsigned int currentSegmentIndex = 1;

	Race();
	~Race();

	void setSegmentsPositions(std::vector<sf::Vector2f> segmentsPositions);

	Segment* getMap();
	void playerMode();
	void aiMode(std::vector<sf::Vector2f> segs, std::vector<int> dirs);
	void endGame();
	void endAIMode();
	float getCarX();
	float getCarY();
	sf::Vector2f getCarPosition();
	float getCarDir();
	float getCarSpeed();
	float getCarTurn();

	// sensors

	float getCarToTrackDistance();
	float getCarDirectionToTrackAngle();
	float getCarToTrackAngle();
	// update that car reached next segment
	void updateSegmentIndex();

	// for debug

	// get on which side of track car currently is
	// false - left
	// true - right
	bool getCurrentCarSide();
	unsigned int getCurrentSegmentIndex();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_MODEL_H

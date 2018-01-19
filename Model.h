#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define _USE_MATH_DEFINES
#include <cmath>
#else
#include <math.h>
#endif

#ifndef LEVEL5AUTONOMOUS_DRIVING_MODEL_H
#define LEVEL5AUTONOMOUS_DRIVING_MODEL_H

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
	Segment *segList;			// current track
	int k;
	
	Track();
	~Track();
	
	void update(float posX, float posY, float faceDir, int segmentType, float rads);				// replace old segments with new ones
};


class Race
{
public:
	Car *vehicle;
	Track *map;
	
	Race();
	~Race();
	
	Segment* getMap();
	
	float getCarX();
	float getCarY();
	float getCarDir();
	float getCarSpeed();
	float getCarTurn();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_MODEL_H
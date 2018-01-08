#define TRACK_SIZE 16

class Race
{
public:
	Car *vehicle;
	Track *map;
	
	Race();
	~Race();
};


class ViewCar
{
public:
	float x, y, dir;			// car's current position and direction it's facing
	
	ViewCar();
	~ViewCar();
};


class ViewTrack
{
public:
	Segment *segList;			// current track
	int k;
	
	ViewTrack();
	~ViewTrack();
	
	void update(float posX, float posY, float faceDir, int segmentType, float rads);				// replace old segments with new ones
};


class ViewSegment
{
public:
	float x, y, dir;
	int segType;
	
	float rad;					// turn degree (0 for straight segments)
	
	ViewSegment();
	ViewSegment(float posX, float posY, float faceDir, int segmentType, float rads);
	~ViewSegment();
	
	void setSegment(float posX, float posY, float faceDir, int segmentType, float rads);
};

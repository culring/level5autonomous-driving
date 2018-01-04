#include "Model.h"


Model::Model()
{
	vehicle = new Car;
	map = new Track;
}

Model::~Model()
{
	delete vehicle;
	delete map;
}



Car::Car()
{
	x = 0;
	y = 0;
	dir = 0.0f;
}

Car::~Car()
{
	
}


Track::Track()
{
	k = 0;
	segList = new Segment[TRACK_SIZE];
}

Track::~Track()
{
	delete[] segList;
}
	
void Track::Update(float posX, float posY, float faceDir, int segmentType, float rads)
{
	segList[k].setSegment(float posX, float posY, float faceDir, int segmentType, float rads);
	
	k = ++k % TRACK_SIZE;
}



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

~Segment::Segment()
{
	
}

void Segment::setSegment(float posX, float posY, float faceDir, int segmentType, float rads)
{
	x = posX;
	y = posY;
	dir = faceDir;
	segType = segmentType;
	rad = rads;
}
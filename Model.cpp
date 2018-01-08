#include "Model.h"


Race::Race()
{
	vehicle = new ViewCar;
	map = new ViewTrack;
}

Race::~Race()
{
	delete vehicle;
	delete map;
}



ViewCar::ViewCar()
{
	x = 0;
	y = 0;
	dir = 0.0f;
}

ViewCar::~ViewCar()
{

}


ViewTrack::ViewTrack()
{
	k = 0;
	segList = new ViewSegment[TRACK_SIZE];
}

ViewTrack::~ViewTrack()
{
	delete[] segList;
}

void ViewTrack::update(float posX, float posY, float faceDir, int segmentType, float rads)
{
	segList[k].setSegment(float posX, float posY, float faceDir, int segmentType, float rads);

	k = ++k % TRACK_SIZE;
}



ViewSegment::ViewSegment()
{
	x = 0;
	y = 0;
	dir = 0;
	segType = 0;
	rad = 0.0f;
}

ViewSegment::ViewSegment(float posX, float posY, float faceDir, int segmentType, float rads)
{
	x = posX;
	y = posY;
	dir = faceDir;
	segType = segmentType;
	rad = rads;
}

~ViewSegment::ViewSegment()
{

}

void ViewSegment::setSegment(float posX, float posY, float faceDir, int segmentType, float rads)
{
	x = posX;
	y = posY;
	dir = faceDir;
	segType = segmentType;
	rad = rads;
}

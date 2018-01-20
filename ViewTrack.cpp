//
// Created by Culring on 2018-01-04.
//

#include "ViewTrack.h"

bool ViewTrack::isOrientationHorizontal()
{
	return (orientation == NEGATIVE_X || orientation == POSITIVE_X) ? true : false;
}

bool ViewTrack::isOrientationVertical()
{
	return (orientation == NEGATIVE_Y || orientation == POSITIVE_Y) ? true : false;
}

ViewTrack::ViewTrack(sf::RenderWindow* window) : m_window(window)
{
	ViewSegment::init();

	// generate track
	srand(time(nullptr));
	for(int i = 0; i < 30; ++i)
	{
		int random = rand() % 3;
//		auto newPosition = calculateNewPosition();
//		
//		if(segmentsInWorld.find(newPosition) != segmentsInWorld.end())
//		{
//			if(!((isOrientationVertical() && segmentsInWorld[newPosition] == HORIZONTAL_STRAIGHT) ||
//				(isOrientationHorizontal() && segmentsInWorld[newPosition] == VERTICAL_STRAIGHT)))
//			{
//				--i;
//				continue;
//			}
//		}

		updatePosition();
		switch(random)
		{
		case 0:
			addSegmentLeft();
			break;
		case 1:
			addSegmentStraight();
			break;
		case 2:
			addSegmentRight();
			break;
		default:
			throw std::exception();
		}
	}
}

std::pair<int, int> ViewTrack::calculateNewPosition(Direction direction)
{
	int coordinateX = m_coordinatesVector.first, 
		coordinateY = m_coordinatesVector.second;

	if (orientation == NEGATIVE_X)
	{
		--coordinateX;
	}
	else if (orientation == POSITIVE_X)
	{
		++coordinateX;
	}
	else if (orientation == NEGATIVE_Y)
	{
		--coordinateY;
	}
	else if (orientation == POSITIVE_Y)
	{
		++coordinateY;
	}

	return {coordinateX, coordinateY};
}

void ViewTrack::updatePosition()
{
//	m_coordinatesVector = calculateNewPosition();
}

void ViewTrack::addSegment(ViewSegmentType segment){

	m_segments.push_back(segment);
    m_sprites.push_back(ViewSegment::createSegment(segment));
    sf::Sprite &sprite = m_sprites.back();
    float distance = ViewSegment::getDistanceToBorder(segment);

    if(orientation == POSITIVE_X) {
		sprite.setPosition(previousX+distance+previousDistance, previousY);
	} else if(orientation == NEGATIVE_X) {
		sprite.setPosition(previousX-distance-previousDistance, previousY);
	} else if(orientation == POSITIVE_Y) {
		sprite.setPosition(previousX, previousY-distance-previousDistance);
	} else if(orientation == NEGATIVE_Y){
		sprite.setPosition(previousX, previousY+distance+previousDistance);
	}

    if(orientation == POSITIVE_X || orientation == NEGATIVE_X) {
    	if(segment == BOTTOM_LEFT || segment == BOTTOM_RIGHT) {
    		orientation = POSITIVE_Y;
    	} else if(segment == TOP_LEFT || segment == TOP_RIGHT) {
    		orientation = NEGATIVE_Y;
    	}
    } else {
    	if(segment == TOP_LEFT || segment == BOTTOM_LEFT) {
    		orientation = POSITIVE_X;
    	} else if(segment == TOP_RIGHT || segment == BOTTOM_RIGHT) {
    		orientation = NEGATIVE_X;
    	}
    }

    previousDistance = distance;
    previousX = sprite.getPosition().x;
    previousY = sprite.getPosition().y;

	segmentsInWorld[m_coordinatesVector] = segment;
}

void ViewTrack::display() {
	for(auto sprite : m_sprites) {
		m_window->draw(sprite);
	}
}

void ViewTrack::addSegmentLeft()
{
	if(orientation == POSITIVE_X)
	{
		addSegment(BOTTOM_RIGHT);
	}
	else if(orientation == NEGATIVE_X)
	{
		addSegment(TOP_LEFT);
	}
	else if(orientation == NEGATIVE_Y)
	{
		addSegment(BOTTOM_LEFT);
	}
	else if(orientation == POSITIVE_Y)
	{
		addSegment(TOP_RIGHT);
	}
	else
	{
		throw std::exception();
	}
}

void ViewTrack::addSegmentRight()
{
	if (orientation == POSITIVE_X)
	{
		addSegment(TOP_RIGHT);
	}
	else if (orientation == NEGATIVE_X)
	{
		addSegment(BOTTOM_LEFT);
	}
	else if (orientation == NEGATIVE_Y)
	{
		addSegment(BOTTOM_RIGHT);
	}
	else if (orientation == POSITIVE_Y)
	{
		addSegment(TOP_LEFT);
	}
	else
	{
		throw std::exception();
	}
}

void ViewTrack::addSegmentStraight()
{
	if(orientation == POSITIVE_X || orientation == NEGATIVE_X)
	{
		addSegment(HORIZONTAL_STRAIGHT);
	}
	else
	{
		addSegment(VERTICAL_STRAIGHT);
	}
}

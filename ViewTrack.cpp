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
//	addSegment(HORIZONTAL_STRAIGHT);
//	addSegment(TOP_RIGHT);
//	addSegment(BOTTOM_RIGHT);
//	addSegment(BOTTOM_LEFT);
//	addSegment(VERTICAL_STRAIGHT);
//	addSegment(TOP_LEFT);
//	addSegment(HORIZONTAL_STRAIGHT);
//	addSegment(HORIZONTAL_STRAIGHT);

	// generate track
	srand(time(nullptr));
	for(int i = 0; i < 30; ++i)
	{
		int random = rand() % 3;
		auto newPosition = calculateNewPosition();
		bool isAdded = true;
		switch(random)
		{
		case 0:
			addSegmentLeft();

//			if(segmentsInWorld.find(newPosition) == segmentsInWorld.end())
//			{
//				addSegmentLeft();
//			}
//			else
//			{
//				isAdded = false;
//			}
			break;
		case 1:
			addSegmentStraight();

			// if straight lines overlap
			if((isOrientationHorizontal() && segmentsInWorld[newPosition] == VERTICAL_STRAIGHT) ||
				(isOrientationVertical() && segmentsInWorld[newPosition] == HORIZONTAL_STRAIGHT) ||
				segmentsInWorld.find(newPosition) == segmentsInWorld.end())
			{
				addSegmentStraight();
			}
			else
			{
				isAdded = false;
			}
			break;
		case 2:
			addSegmentRight();

//			if (segmentsInWorld.find(newPosition) == segmentsInWorld.end()) {
//				addSegmentRight();
//			}
//			else
//			{
//				isAdded = false;
//			}
			break;
		default:
			throw std::exception();
		}
		if(isAdded)
		{
//			std::cout << random << std::endl;
//			std::cout << newPosition.first << " " << newPosition.second << std::endl;
			updatePosition();
		}
		else
		{
			// repeat iteration
			--i;
		}
	}
}

std::pair<int, int> ViewTrack::calculateNewPosition()
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
	m_coordinatesVector = calculateNewPosition();
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

//
// Created by Culring on 2018-01-04.
//

#include "ViewTrack.h"

bool ViewTrack::isOrientationHorizontal(Orientation orientation)
{
	return (orientation == NEGATIVE_X || orientation == POSITIVE_X) ? true : false;
}

bool ViewTrack::isOrientationVertical(Orientation orientation)
{
	return (orientation == NEGATIVE_Y || orientation == POSITIVE_Y) ? true : false;
}

bool ViewTrack::areSegmentsOpposite(ViewSegmentType segmentA, ViewSegmentType segmentB)
{
	if(segmentA == TOP_LEFT)
	{
		return (segmentB == BOTTOM_RIGHT) ? true : false;
	}
	else if(segmentA == BOTTOM_RIGHT)
	{
		return (segmentB == TOP_LEFT) ? true : false;
	}
	else if(segmentA == TOP_RIGHT)
	{
		return (segmentB == BOTTOM_LEFT) ? true : false;
	}
	else if(segmentA == BOTTOM_LEFT)
	{
		return (segmentB == TOP_RIGHT) ? true : false;
	}
}

Orientation ViewTrack::checkNextOrientationFromSegment(ViewSegmentType segment)
{
	if (m_orientation == POSITIVE_X || m_orientation == NEGATIVE_X) {
		if (segment == BOTTOM_LEFT || segment == BOTTOM_RIGHT) {
			return POSITIVE_Y;
		}
		else if (segment == TOP_LEFT || segment == TOP_RIGHT) {
			return NEGATIVE_Y;
		}
	}
	else {
		if (segment == TOP_LEFT || segment == BOTTOM_LEFT) {
			return POSITIVE_X;
		}
		else if (segment == TOP_RIGHT || segment == BOTTOM_RIGHT) {
			return NEGATIVE_X;
		}
	}

	return m_orientation;
}

Orientation ViewTrack::checkNextOrientationFromDirection(Direction direction)
{
	ViewSegmentType segment = getSegmentToDirection(direction);
	return checkNextOrientationFromSegment(segment);

	return m_orientation;
}

ViewSegmentType ViewTrack::getSegmentToLeft()
{
	if (m_orientation == POSITIVE_X)
	{
		return BOTTOM_RIGHT;
	}
	else if (m_orientation == NEGATIVE_X)
	{
		return TOP_LEFT;
	}
	else if (m_orientation == NEGATIVE_Y)
	{
		return BOTTOM_LEFT;
	}
	else if (m_orientation == POSITIVE_Y)
	{
		return TOP_RIGHT;
	}
	else
	{
		throw std::exception();
	}
}

ViewSegmentType ViewTrack::getSegmentToRight()
{
	if (m_orientation == POSITIVE_X)
	{
		return TOP_RIGHT;
	}
	else if (m_orientation == NEGATIVE_X)
	{
		return BOTTOM_LEFT;
	}
	else if (m_orientation == NEGATIVE_Y)
	{
		return BOTTOM_RIGHT;
	}
	else if (m_orientation == POSITIVE_Y)
	{
		return TOP_LEFT;
	}
	else
	{
		throw std::exception();
	}
}

ViewSegmentType ViewTrack::getSegmentStraight()
{
	if (m_orientation == POSITIVE_X || m_orientation == NEGATIVE_X)
	{
		return HORIZONTAL_STRAIGHT;
	}
	else
	{
		return VERTICAL_STRAIGHT;
	}
}

ViewSegmentType ViewTrack::getSegmentToDirection(Direction direction)
{
	if(direction == LEFT)
	{
		return getSegmentToLeft();
	}
	else if(direction == RIGHT)
	{
		return getSegmentToRight();
	}
	else if(direction == STRAIGHT)
	{
		return getSegmentStraight();
	}
	else
	{
		throw std::exception();
	}
}

ViewTrack::ViewTrack(sf::RenderWindow* window) : m_window(window)
{
	ViewSegment::init();

	// generate track
	srand(time(nullptr));
	for(int i = 0, j = 0; i < 1000; ++i)
	{
		int random = rand() % 3;
//
//		std::cout << "(x,y) = " << "(" << m_coordinatesVector.first << ", " << m_coordinatesVector.second << ")" << std::endl;
//		auto nextCoordinates = checkNextPosition(LEFT);
//		std::cout << isOrientationVertical(checkNextOrientationFromDirection(LEFT)) << ": (" << nextCoordinates.first << ", " << nextCoordinates.second << ")" << std::endl;
//		nextCoordinates = checkNextPosition(STRAIGHT);
//		std::cout << isOrientationVertical(checkNextOrientationFromDirection(STRAIGHT)) << ": (" << nextCoordinates.first << ", " << nextCoordinates.second << ")" << std::endl;
//		nextCoordinates = checkNextPosition(RIGHT);
//		std::cout << isOrientationVertical(checkNextOrientationFromDirection(RIGHT)) << ": (" << nextCoordinates.first << ", " << nextCoordinates.second << ")" << std::endl;

		if (j == 10)
		{
			std::cout << "Number of generated segments: " << i+1 << std::endl;
			break;
		}

		auto nextOrientation = checkNextOrientationFromDirection((Direction)random);
		auto nextCoordinates = checkNextPosition((Direction)random);
		auto segmentLeft = getSegmentToLeft(),
			segmentRight = getSegmentToRight();
		if (segmentsInWorld.find(nextCoordinates) != segmentsInWorld.end())
		{
//			auto nextSegmentInWorld = segmentsInWorld[nextCoordinates];
//			if (!((isOrientationVertical(nextOrientation) && nextSegmentInWorld == HORIZONTAL_STRAIGHT) ||
//				(isOrientationHorizontal(nextOrientation) && nextSegmentInWorld == VERTICAL_STRAIGHT) ||
//				areSegmentsOpposite(segmentLeft, nextSegmentInWorld) ||
//				areSegmentsOpposite(segmentRight, nextSegmentInWorld)))
//			{

			auto nextSegmentInWorld = segmentsInWorld[nextCoordinates];
			if (!((isOrientationVertical(nextOrientation) && nextSegmentInWorld == HORIZONTAL_STRAIGHT) ||
				(isOrientationHorizontal(nextOrientation) && nextSegmentInWorld == VERTICAL_STRAIGHT)))
			{

				--i;
				++j;
				continue;
			}
		}

		j = 0;

//		std::cout << i << std::endl;

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

		m_coordinatesVector = nextCoordinates;
//		std::cout << "(x,y) = " << "(" << m_coordinatesVector.first << ", " << m_coordinatesVector.second << ")" << std::endl;
//		getchar();
	}
}

std::pair<int, int> ViewTrack::checkNextPosition(Direction direction)
{
	int coordinateX = m_coordinatesVector.first, 
		coordinateY = m_coordinatesVector.second;

	Orientation orientation = checkNextOrientationFromDirection(direction);

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
//	m_coordinatesVector = checkNextPosition();
}

void ViewTrack::addSegment(ViewSegmentType segment){

	m_segments.push_back(segment);
    m_sprites.push_back(ViewSegment::createSegment(segment));
    sf::Sprite &sprite = m_sprites.back();
    float distance = ViewSegment::getDistanceToBorder(segment);

	if (m_orientation == POSITIVE_X) {
		m_currentPosition.x += distance;
	}
	else if (m_orientation == NEGATIVE_X) {
		m_currentPosition.x -= distance;
	}
	else if (m_orientation == POSITIVE_Y) {
		m_currentPosition.y -= distance;
	}
	else if (m_orientation == NEGATIVE_Y) {
		m_currentPosition.y += distance;
	}
	sprite.setPosition(m_currentPosition);
	m_orientation = checkNextOrientationFromSegment(segment);
	if (m_orientation == POSITIVE_X) {
		m_currentPosition.x += distance;
	}
	else if (m_orientation == NEGATIVE_X) {
		m_currentPosition.x -= distance;
	}
	else if (m_orientation == POSITIVE_Y) {
		m_currentPosition.y -= distance;
	}
	else if (m_orientation == NEGATIVE_Y) {
		m_currentPosition.y += distance;
	}

	segmentsInWorld[m_coordinatesVector] = segment;
}

void ViewTrack::display() {
	for(auto sprite : m_sprites) {
		m_window->draw(sprite);
	}
}

void ViewTrack::addSegmentLeft()
{
	addSegment(getSegmentToLeft());
}

void ViewTrack::addSegmentRight()
{
	addSegment(getSegmentToRight());
}

void ViewTrack::addSegmentStraight()
{
	addSegment(getSegmentStraight());
}

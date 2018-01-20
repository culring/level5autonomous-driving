//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_TRACK_H
#define LEVEL5AUTONOMOUS_DRIVING_TRACK_H

#include <vector>
#include "ViewSegment.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Textures.h"

enum Orientation {
	POSITIVE_X,
	NEGATIVE_X,
	POSITIVE_Y,
	NEGATIVE_Y
};

enum Direction
{
	LEFT,
	STRAIGHT,
	RIGHT
};

class ViewTrack {
	Orientation m_orientation = POSITIVE_X;
	sf::Vector2f m_currentPosition = {640, 480}; 

	// variables useful in generating map
	std::pair<int, int> m_coordinatesVector;
	std::map<std::pair<int, int>, ViewSegmentType> segmentsInWorld;

    std::vector<ViewSegmentType> m_segments;
	sf::RenderWindow *m_window;
	std::vector<sf::Sprite> m_sprites;

	bool isOrientationHorizontal(Orientation orientation);
	bool isOrientationVertical(Orientation orientation);
	bool areSegmentsOpposite(ViewSegmentType segmentA, ViewSegmentType segmentB);
	Orientation checkNextOrientationFromSegment(ViewSegmentType segment);
	Orientation checkNextOrientationFromDirection(Direction direction);
	ViewSegmentType getSegmentToLeft();
	ViewSegmentType getSegmentToRight();
	ViewSegmentType getSegmentStraight();
	ViewSegmentType getSegmentToDirection(Direction direction);
	void addSegment(ViewSegmentType segment);
	std::pair<int, int> checkNextPosition(Direction direction);

public:
	ViewTrack(sf::RenderWindow *window);
	void updatePosition();
    void display();
	void addSegmentLeft();
	void addSegmentRight();
	void addSegmentStraight();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_TRACK_H

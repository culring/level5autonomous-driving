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

class ViewTrack {
	Orientation orientation = POSITIVE_X;
	float previousX=640, previousY=360, previousDistance=-400;

	// variables useful in generating map
	std::pair<int, int> m_coordinatesVector;
	std::map<std::pair<int, int>, ViewSegmentType> segmentsInWorld;

    std::vector<ViewSegmentType> m_segments;
	sf::RenderWindow *m_window;
	std::vector<sf::Sprite> m_sprites;

	bool isOrientationHorizontal();
	bool isOrientationVertical();

public:
	ViewTrack(sf::RenderWindow *window);
	std::pair<int, int> calculateNewPosition();
	void updatePosition();
    void addSegment(ViewSegmentType segment);
    void display();
	void addSegmentLeft();
	void addSegmentRight();
	void addSegmentStraight();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_TRACK_H

//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_TRACK_H
#define LEVEL5AUTONOMOUS_DRIVING_TRACK_H

#include <vector>
#include "ViewSegment.h"
#include <SFML/Graphics.hpp>

enum Orientation {
	POSITIVE_X,
	NEGATIVE_X,
	POSITIVE_Y,
	NEGATIVE_Y
};

class ViewTrack {
	Orientation orientation = POSITIVE_X;
	float previousX=640, previousY=360, previousDistance=-400;
    std::vector<ViewSegmentType> m_segments;
	sf::RenderWindow *m_window;
	std::vector<sf::Sprite> m_sprites;

public:
	ViewTrack(sf::RenderWindow *window);
    void addSegment(ViewSegmentType segment);
    void display();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_TRACK_H

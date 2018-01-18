//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_TRACK_H
#define LEVEL5AUTONOMOUS_DRIVING_TRACK_H

#include <vector>
#include "ViewSegment.h"
#include <SFML/Graphics.hpp>

class ViewTrack {
    std::vector<ViewSegmentType> m_segments;
	sf::RenderWindow *m_window;
	std::vector<sf::Sprite> m_sprites;

public:
	ViewTrack(sf::RenderWindow *window);
    void addSegment(ViewSegmentType segment);
};

#endif //LEVEL5AUTONOMOUS_DRIVING_TRACK_H

//
// Created by Culring on 2018-01-04.
//

#include "ViewTrack.h"
#include "Textures.h"

ViewTrack::ViewTrack(sf::RenderWindow* window) : m_window(window)
{
	ViewSegment::init();
	addSegment(HORIZONTAL_STRAIGHT);
	addSegment(TOP_RIGHT);
	addSegment(BOTTOM_RIGHT);
	addSegment(BOTTOM_LEFT);
	addSegment(VERTICAL_STRAIGHT);
	addSegment(TOP_LEFT);
	addSegment(HORIZONTAL_STRAIGHT);
	addSegment(HORIZONTAL_STRAIGHT);

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
}

void ViewTrack::display() {
	for(auto sprite : m_sprites) {
		m_window->draw(sprite);
	}
}

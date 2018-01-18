//
// Created by Culring on 2018-01-04.
//

#include "ViewTrack.h"
#include "Textures.h"

ViewTrack::ViewTrack(sf::RenderWindow* window) : m_window(window)
{
	verticalStraightRoadTexture.loadFromFile(ROAD_TEXTURES_DIRECTORY, VERTICAL_STRAIGHT_ROAD_RECTANGLE);
}

void ViewTrack::addSegment(ViewSegmentType segment){
    m_segments.push_back(segment);
}

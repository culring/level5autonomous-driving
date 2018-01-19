//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H
#define LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H

#include <SFML/System/Vector2.hpp>
#include <exception>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Textures.h"
#include <iostream>

enum ViewSegmentType {
	VERTICAL_STRAIGHT,
	HORIZONTAL_STRAIGHT,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT
};

class ViewSegment {
public:
	static sf::Texture verticalStraightTexture, bottomRightTexture;
	static constexpr float scale = 0.3f;
	ViewSegment() = delete;

	static void init()
	{
		if(!verticalStraightTexture.loadFromFile(ROAD_TEXTURES_DIRECTORY, STRAIGHT_ROAD_RECTANGLE))
		{
			throw std::exception();
		}

		if (!bottomRightTexture.loadFromFile(ROAD_TEXTURES_DIRECTORY, CORNER_ROAD_RECTANGLE))
		{
			throw std::exception();
		}
	}

	static sf::Sprite createSegment(ViewSegmentType segmentType)
	{
		sf::Sprite sprite;

		switch (segmentType)
		{
			case VERTICAL_STRAIGHT:
				sprite.setTexture(verticalStraightTexture);
				sprite.setOrigin(getCenter(ViewSegmentType::VERTICAL_STRAIGHT));
				break;
			case HORIZONTAL_STRAIGHT:
				sprite.setTexture(verticalStraightTexture);
				sprite.rotate(90.0f);
				sprite.setOrigin(getCenter(ViewSegmentType::VERTICAL_STRAIGHT));
				break;
			case TOP_LEFT:
				sprite.setTexture(bottomRightTexture);
				sprite.rotate(180.0f);
				sprite.setOrigin(getCenter(ViewSegmentType::BOTTOM_RIGHT));
				break;
			case TOP_RIGHT:
				sprite.setTexture(bottomRightTexture);
				sprite.rotate(-90.0f);
				sprite.setOrigin(getCenter(ViewSegmentType::BOTTOM_RIGHT));
				break;
			case BOTTOM_RIGHT:
				sprite.setTexture(bottomRightTexture);
				sprite.setOrigin(getCenter(ViewSegmentType::BOTTOM_RIGHT));
				break;
			case BOTTOM_LEFT:
				sprite.setTexture(bottomRightTexture);
				sprite.rotate(90.0f);
				sprite.setOrigin(getCenter(ViewSegmentType::BOTTOM_LEFT));
				break;
			default:
				throw std::exception();
		}

		sprite.scale(scale, scale);
		return sprite;
	}

	static sf::Vector2f getCenter(ViewSegmentType segmentType)
	{
		switch(segmentType)
		{
			case VERTICAL_STRAIGHT:
				return {352.5, 512};
				break;
			case HORIZONTAL_STRAIGHT:
				return {512, 352.5};
				break;
			case TOP_LEFT:
				return {352.5, 352.5};
				break;
			case TOP_RIGHT:
				return {509.5, 352.5};
				break;
			case BOTTOM_RIGHT:
				return {509.5, 509.5};
				break;
			case BOTTOM_LEFT:
				return {509.5, 509.5};
				break;
			default:
				throw std::exception();
		}
	}

	static float getDistanceToBorder(ViewSegmentType segmentType)
	{
		float distance;

		switch(segmentType)
		{
			case VERTICAL_STRAIGHT:
				distance = 512.0f;
				break;
			case HORIZONTAL_STRAIGHT:
				distance = 512.0f;
				break;
			case TOP_LEFT:
				distance = 509.5f;
				break;
			case TOP_RIGHT:
				distance = 509.5f;
				break;
			case BOTTOM_RIGHT:
				distance = 509.5f;
				break;
			case BOTTOM_LEFT:
				distance = 509.5f;
				break;
			default:
				throw std::exception();
		}

		return scale * distance;
	}
};

#endif //LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H

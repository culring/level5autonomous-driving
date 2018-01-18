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

enum ViewSegmentType {
	VERTICAL_STRAIGHT,
	HORIZONTAL_STRAIGHT,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT
};

class ViewSegment {
	static sf::Texture verticalStraightTexture,
		bottomRightTexture;
public:
	ViewSegment() = delete;
	static void init()
	{
		if(!verticalStraightTexture.loadFromFile(ROAD_TEXTURES_DIRECTORY, STRAIGHT_ROAD_RECTANGLE))
		{
			throw std::exception("Texture file not found");
		}
		if (!bottomRightTexture.loadFromFile(ROAD_TEXTURES_DIRECTORY, CORNER_ROAD_RECTANGLE))
		{
			throw std::exception("Texture file not found");
		}
	}
	static sf::Sprite createSegment(ViewSegmentType segmentType)
	{
		sf::Sprite sprite;
		switch (segmentType)
		{
			case VERTICAL_STRAIGHT:
				sprite.setTexture(verticalStraightTexture);
				sprite.move(-getCenter(ViewSegmentType::VERTICAL_STRAIGHT)*0.5f);
				break;
			case HORIZONTAL_STRAIGHT:
				sprite.setTexture(verticalStraightTexture);
				sprite.move((sf::Vector2f)verticalStraightTexture.getSize()*-0.5f);
				sprite.rotate(90.0f);
				sprite.move((sf::Vector2f)verticalStraightTexture.getSize()*0.5f);
				sprite.move(-getCenter(ViewSegmentType::HORIZONTAL_STRAIGHT)*0.5f);
				break;
			case TOP_LEFT:
				sprite.setTexture(bottomRightTexture);
				sprite.move((sf::Vector2f)bottomRightTexture.getSize()*-0.5f);
				sprite.rotate(180.0f);
				sprite.move((sf::Vector2f)bottomRightTexture.getSize()*0.5f);
				sprite.move(-getCenter(ViewSegmentType::TOP_LEFT)*0.5f);
				break;
			case TOP_RIGHT:
				sprite.setTexture(bottomRightTexture);
				sprite.move((sf::Vector2f)bottomRightTexture.getSize()*-0.5f);
				sprite.rotate(90.0f);
				sprite.move((sf::Vector2f)bottomRightTexture.getSize()*0.5f);
				sprite.move(-getCenter(ViewSegmentType::TOP_RIGHT)*0.5f);
				return sprite;
				break;
			case BOTTOM_RIGHT:
				sprite.setTexture(bottomRightTexture);
				sprite.move(-getCenter(ViewSegmentType::BOTTOM_RIGHT)*0.5f);
				break;
			case BOTTOM_LEFT:
				sprite.setTexture(bottomRightTexture);
				sprite.move((sf::Vector2f)bottomRightTexture.getSize()*-0.5f);
				sprite.rotate(-90.0f);
				sprite.move((sf::Vector2f)bottomRightTexture.getSize()*0.5f);
				sprite.move(-getCenter(ViewSegmentType::BOTTOM_LEFT)*0.5f);
				break;
			default:
				throw std::exception("Segment type not found");
		}
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
				return {352.5, 509.5};
				break;
			default:
				throw std::exception("Segment type not found");
		}
	}
	static float getDistanceToBorder(ViewSegmentType segmentType)
	{
		switch(segmentType)
		{
			case VERTICAL_STRAIGHT:
				return 512.0f;
				break;
			case HORIZONTAL_STRAIGHT:
				return 512.0f;
				break;
			case TOP_LEFT:
				return 509.5f;
				break;
			case TOP_RIGHT:
				return 509.5f;
				break;
			case BOTTOM_RIGHT:
				return 509.5f;
				break;
			case BOTTOM_LEFT:
				return 509.5f;
				break;
			default:
				throw std::exception("Segment type not found");
		}
	}
};

#endif //LEVEL5AUTONOMOUS_DRIVING_SEGMENT_H

//
// Created by Culring on 2018-01-04.
//

#include "ViewCar.h"
#include "Textures.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

ViewCar::ViewCar(sf::RenderWindow *window) : m_window(window)
{
	//std::cout << GetCurrentWorkingDir() << std::endl;
	if (!texture.loadFromFile(CAR_TEXTURES_DIRECTORY, CAR_RECTANGLE))
	{
		throw std::exception("Texture file not found");	
	}
	sprite.setTexture(texture);
	auto vector = m_window->getSize();
	sprite.setPosition((float)vector.x/2, (float)vector.y/2);
	sprite.scale(0.25f, 0.25f);
}

void ViewCar::updatePosition(float positionX, float positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
}

void ViewCar::updateDirection(float direction){
    m_direction = direction;
}

void ViewCar::display()
{
	m_window->draw(sprite);
}

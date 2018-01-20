//
// Created by Culring on 2018-01-04.
//

#include "ViewCar.h"
#include "Textures.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

ViewCar::ViewCar(sf::RenderWindow *window) : m_window(window), m_positionX(0), m_positionY(0), m_direction(0)
{
	//std::cout << GetCurrentWorkingDir() << std::endl;
	if (!texture.loadFromFile(CAR_TEXTURES_DIRECTORY, CAR_RECTANGLE))
	{
		throw std::exception();
	}

	sprite.setTexture(texture);
	sprite.setOrigin(89.5, 153);
	sprite.scale(0.2f, 0.2f);
}

void ViewCar::updatePosition(float positionX, float positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
    sprite.setPosition(positionX, positionY);

	sf::View view = m_window->getView();
	view.setCenter(positionX, positionY);
	m_window->setView(view);
}

void ViewCar::updateDirection(float direction){
	sprite.setRotation(direction+90);
    m_direction = direction;
}

void ViewCar::display()
{
	m_window->draw(sprite);
}

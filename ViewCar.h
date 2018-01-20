//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_CAR_H
#define LEVEL5AUTONOMOUS_DRIVING_CAR_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class ViewCar {
	// window
	sf::RenderWindow *m_window;
    // current car's position
    float m_positionX, m_positionY;
    // current car's m_orientation
    float m_direction;
	//sprite
	sf::Sprite sprite;
	sf::Texture texture;

    void move();

public:
	ViewCar(sf::RenderWindow *window);

    void updatePosition(float positionX, float positionY);
    void updateDirection(float direction);
	void display();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_CAR_H

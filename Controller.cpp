//============================================================================
// Name        : Controller.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "Controller.h"

Controller::Controller(sf::RenderWindow &w) {
	this->window = &w;
}

/*
Controller::Controller(Model m, View v) {
	this->model = m;
	this->view = v;
	this->window = v->window;
}
*/

Controller::~Controller() {
	this->window->~RenderWindow();
}

void Controller::menu() {
	sf::Event event;
	std::cout << "menu" << std::endl;

	while(this->window->isOpen()) {
		while(this->window->pollEvent(event)) {
			if(event.type == sf::Event::EventType::KeyPressed) {
				if(sf::Keyboard::Key::Num1 == event.key.code) {
					// e.g. start player mode
					//this->view.initPlayerMode();
					//this->model.initPlayerMode();
					std::cout << "init playerMode" << std::endl;
					playerMode();
				} else if(sf::Keyboard::Key::Num2 == event.key.code) {
					std::cout << "init aiMode" << std::endl;
					aiMode();
				}
			} else if (event.type == sf::Event::EventType::Closed) {
				std::cout << "Closing..." << std::endl;
				this->window->close();
			}

			this->window->display();
		}
	}
}

void Controller::playerMode() {
	sf::Event event;
	bool end = false;
	std::cout << "playerMode" << std::endl;

	while(this->window->isOpen()) {
		while(this->window->pollEvent(event)) {
			if(event.type == sf::Event::EventType::KeyPressed) {
				if(sf::Keyboard::Key::Left == event.key.code || sf::Keyboard::Key::A == event.key.code) {
					//turn left
					std::cout << "Pressed left" << std::endl;
				} else if(sf::Keyboard::Key::Right == event.key.code || sf::Keyboard::Key::D == event.key.code) {
					//turn right
					std::cout << "Pressed right" << std::endl;
				} else if(sf::Keyboard::Key::Up == event.key.code || sf::Keyboard::Key::W == event.key.code) {
					//accelerate
					std::cout << "Pressed up" << std::endl;
				} else if(sf::Keyboard::Key::Down == event.key.code || sf::Keyboard::Key::S == event.key.code) {
					//decelerate
					std::cout << "Pressed down" << std::endl;
				} else if(sf::Keyboard::Key::Escape == event.key.code) {
					//end race, back to menu
					//model.endRace();
					//view.endRace();
					std::cout << "Pressed Escape - back to menu" << std::endl;
					end = true;
					break;
				}
			} else if(event.type == sf::Event::EventType::Closed) {
				 this->window->close();
			}

			this->window->display();
		}

		if(end == true) break;
	}
}

void Controller::aiMode() {
	sf::Event event;
	bool end = false;
	std::cout << "aiMode" << std::endl;

	while(this->window->isOpen()) {
		while(this->window->pollEvent(event)) {
			if(event.type == sf::Event::EventType::KeyPressed) {
				if(sf::Keyboard::Key::Escape == event.key.code) {
					//end race, back to menu
					//model.endRace();
					//view.endRace();
					std::cout << "Pressed Escape - back to menu" << std::endl;
					end = true;
					break;
				}
			} else if(event.type == sf::Event::EventType::Closed) {
				this->window->close();
			}
		}

		if(end == true) break;
	}
}

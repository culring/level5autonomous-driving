//============================================================================
// Name        : Controller.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "Controller.h"

Controller::Controller() {
	this->model = new Race();
	this->view = new View();
	this->view->addModel(model);
	this->window = view->getWindow();
}


/*Controller::Controller(Race *m, View *v) {
	this->model = m;
	this->view = v;
	this->window = v->getWindow();
}*/


Controller::~Controller() {
	this->window->~RenderWindow();
	delete view;
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

			this->window->clear();
			this->view->display();
			this->window->display();
		}
	}
}

void Controller::playerMode() {
	sf::Event event;
	bool end = false;
	std::cout << "playerMode" << std::endl;

	while(this->window->isOpen()) {
		while(1) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				model->vehicle->turnLeft();
				model->vehicle->accel();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				model->vehicle->turnRight();
				model->vehicle->accel();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				model->vehicle->turnLeft();
				model->vehicle->slow();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				model->vehicle->turnRight();
				model->vehicle->slow();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				model->vehicle->turnLeft();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				model->vehicle->turnRight();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				model->vehicle->accel();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				model->vehicle->slow();
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				end=true;
			}

			this->model->vehicle->update();
			this->view->updateCar();
			this->window->clear();
			this->view->display();
			this->window->display();

			if(end == true) break;

			if(event.type == sf::Event::EventType::Closed) {
				this->window->close();
			}
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

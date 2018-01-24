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

	window->setFramerateLimit(60);
}

Controller::~Controller() {
	delete model;
	delete view;
}

void Controller::menu() {
	sf::Event event;
	std::cout << "menu" << std::endl;
	this->view->displayMenu();
	//this->view->menu();
	//this->model->menu();

	while(this->window->isOpen()) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
			this->model->playerMode();
			this->view->gameMode();
			std::cout << "init playerMode" << std::endl;
			playerMode();
			view->resetView();
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
			view->gameMode();
			std::vector<sf::Vector2i> positions = view->getTrack()->getSegmentsPosition();
			std::vector<int> directions = view ->getTrack()->getDirVector();
			model->aiMode(positions, directions);
			std::cout << "init aiMode" << std::endl;
			aiMode();
			view->resetView();
		}

		//this->window->clear();
		this->view->displayMenu();
		this->window->display();

		if (this->window->pollEvent(event) && event.type == sf::Event::EventType::Closed) {
			std::cout << "Closing..." << std::endl;
			this->window->close();
		}
	}
}

void Controller::playerMode() {
	sf::Event event;
	std::cout << "playerMode" << std::endl;

	while(this->window->isOpen()) {
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
			view->endGame();
			model->endGame();
			break;
		}

		this->model->vehicle->update();
		this->view->updateCar();
		this->window->clear();
		this->view->display();
		this->window->display();

		if(this->window->pollEvent(event) && event.type == sf::Event::EventType::Closed) {
			this->window->close();
		}
	}
}

void Controller::aiMode() {
	sf::Event event;
	bool end = false;
	std::cout << "aiMode" << std::endl;

	float turnRate = 30.0f;
	float speedRate = 5.0f;
	float turnValueLeft = 0.0f;
	float turnValueRight = 0.0f;
	float speedValue = 0.0f;
	float distance = 0.0f;
	float direction = 0.0f;
	int segNo = 0;
	float dirSub = 0.0f;


	while(this->window->isOpen()) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			view->endGame();
			model->endAIMode();
			break;
		}

		/*** AI logic ***/
		distance = sqrt((model->segmentsPositions[segNo].x - model->vehicle->x)^2 + (model->segmentsPositions[segNo].y - model->vehicle->y)^2);
		direction = asin(((model->segmentsPositions[segNo].y - model->vehicle->y) * 180.0f) / (distance * M_PI));

		dirSub = model->vehicle->dir - direction;
		turnValue = model->fuzzySetTurn->getValue(dirSub) * turnRate;

		if(dirSub > 0.0f && turnValue > 0.0f && model->vehicle->turn > (-turnValue))
			model->vehicle->turnRight();
		else if (dirSub < 0.0f && turnValue > 0.0f && model->vehicle->turn < turnValue)
			model->vehicle->turnLeft();

		if(model->directions[segNo] == 1)
			speedValue = model->fuzzySetSpeedForStraight->getValue(distance) * speedRate;
		else
			speedValue = model->fuzzySetSpeedForTurn->getValue(distance) * speedRate;

		if(model->vehicle->speed < speedValue)
			model->vehicle->accel();
		else if (model->vehicle->speed > speedValue)
			model->vehicle->slow();

		if(distance <= 10.0f)
			segNo++;

		this->model->vehicle->update();
		this->view->updateCar();
		this->window->clear();
		this->view->display();
		this->window->display();

		if(this->window->pollEvent(event) && event.type == sf::Event::EventType::Closed) {
			this->window->close();
		}
	}
}

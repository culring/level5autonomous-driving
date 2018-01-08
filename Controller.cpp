//============================================================================
// Name        : Controller.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "Controller.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// #include <SFML/Graphics.hpp>

Controller::Controller() {}

/*
Controller::Controller(Model m, View v) {
	this->model = m;
	this->view = v;
	this->window = v->window;
}
*/

Controller::~Controller() {}

void Controller::menu() {
	/*
	sf::Event event;

	while(this->window.isOpen() && this->window.pollEvent(event)) {
		 if(sf::Event::EventType::KeyPressed) {
		 	 if(sf::Keyboard::Key::1 == event.key.code) {
		 	 	 // e.g. start player mode
		 	 	 this->view.initPlayerMode();
		 	 	 this->model.initPlayerMode();
		 	 	 playerMode();
		 	 } ...
		 } else if (sf::Event::EventType::Closed) {
		 	 this->view.closeWindow();
		 }
	}
	*/
}

void Controller::playerMode() {
	/*
	sf::Event event;

	while(this->window.isOpen() && this->window.pollEvent(event)) {
		if(sf::Event::EventType::KeyPressed) {
			if(sf::Keyboard::Key::Left == event.key.code || sf::Keyboard::Key::A == event.key.code) {
				//turn left
			} else if(sf::Keyboard::Key::Right == event.key.code || sf::Keyboard::Key::D == event.key.code) {
				//turn right
			} else if(sf::Keyboard::Key::Up == event.key.code || sf::Keyboard::Key::W == event.key.code) {
				//accelerate
			} else if(sf::Keyboard::Key::Down == event.key.code || sf::Keyboard::Key::S == event.key.code) {
				//decelerate
			} else if(sf::Keyboard::Key::Escape == event.key.code) {
				//end race, back to menu
				model.endRace();
				view.endRace();
				break;
			}
		}
	}
	*/
}

void Controller::aiMode() {
	/*
	sf::Event event;

	while(this->window.isOpen() && this->window.pollEvent(event)) {
		if(sf::Event::EventType::KeyPressed) {
			if(sf::Keyboard::Key::Escape == event.key.code) {
				//end race, back to menu
				model.endRace();
				view.endRace();
				break;
			}
		}
	}
	*/
}

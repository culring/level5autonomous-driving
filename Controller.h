/*
 * Controller.hpp
 *
 *  Created on: 04.01.2018
 *      Author: matinho1706
 */

#ifndef LEVEL5AUTONOMOUS_DRIVING_CONTROLLER_H
#define LEVEL5AUTONOMOUS_DRIVING_CONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "View.h"
#include "Model.h"
#include <SFML/Window/Keyboard.hpp>
#include "FuzzySet.h"
#include "FuzzyDriver.h"

class Controller {
private:
	Race *model;
	View *view;
	sf::RenderWindow *window;

	// fuzzy
	FuzzyDriver fuzzyController;

public:
	Controller();
	//Controller(Race *m, View *v);
	~Controller();
	void menu();
	void playerMode();
	void aiMode();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_CONTROLLER_H

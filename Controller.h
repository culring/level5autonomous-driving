/*
 * Controller.hpp
 *
 *  Created on: 04.01.2018
 *      Author: matinho1706
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "View.h"

class Controller {
private:
	//Model *model;
	View *view;
	sf::RenderWindow *window;
public:
	Controller();
	//Controller(Model m, View v);
	~Controller();
	void menu();
	void playerMode();
	void aiMode();
};

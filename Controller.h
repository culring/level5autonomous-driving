/*
 * Controller.hpp
 *
 *  Created on: 04.01.2018
 *      Author: matinho1706
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class MainController {
private:
	//Model *model;
	//View *view;
	//sf::Window *window;
public:
	MainController();
	//MainController(Model m, View v);
	~MainController();
	void menu();
};

class PlayerController {
private:
	//Model *model;
	//View *view;
	//sf::Window *window;
public:
	PlayerController();
	//PlayerController(Model m, View v);
	~PlayerController();
	void steering();
};

class AIController {
private:
	//Model *model;
	//View *view;
	//sf::Window *window;
public:
	AIController();
	//AIController(Model m, View v);
	~AIController();
	void endRace();
};

#endif /* CONTROLLER_H_ */

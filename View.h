//
// Created by Culring on 2018-01-08.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_VIEW_H
#define LEVEL5AUTONOMOUS_DRIVING_VIEW_H

#include <vector>
#include "Model.h"
#include "ViewCar.h"
#include "ViewTrack.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"

class View {
    // view variables
	sf::RenderWindow *m_window;
    Race *m_model;
    ViewCar *m_viewCar;
    ViewTrack *m_viewTrack;
	sf::Sprite background;
	sf::Texture menuTexture;
	sf::Font font;
	sf::Text playerModeOption;
	sf::Text aiModeOption;
public:
	View();
	~View();
	void addModel(Race *m);
    void initializeRace(std::vector<Segment> segments);
    void updateCar();
	sf::RenderWindow* getWindow();
	ViewTrack *getTrack();
	void menu();
	void gameMode();
	void endGame();
	void displayMenu();
	void display();
	void resetView();
	void initMenuElements();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_VIEW_H

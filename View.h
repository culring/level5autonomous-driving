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

class View {
    // view variables
    ViewCar *m_viewCar;
    ViewTrack *m_viewTrack;
    // model
    Race *m_model;
	sf::RenderWindow *m_window;

public:
	View();
	~View();
    void initializeRace(std::vector<Segment> segments);
    void updateCar();
	sf::RenderWindow* getWindow();
	void display();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_VIEW_H

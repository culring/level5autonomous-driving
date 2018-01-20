//
// Created by Culring on 2018-01-08.
//

#include "View.h"
#include <iostream>

View::View() : 
	m_window(new sf::RenderWindow(sf::VideoMode(1280, 720), "Bylena3:<"))
{
	m_viewCar = new ViewCar(m_window);
	m_viewTrack = new ViewTrack(m_window);

	sf::View view = m_window->getDefaultView();
	view.zoom(2.5f);
	view.setCenter(0, 0);
	m_window->setView(view);
}

View::~View()
{
	delete m_window;
	delete m_viewCar;
	delete m_viewTrack;
}

void View::updateCar() {
    m_viewCar->updatePosition(m_model->getCarX(), m_model->getCarY());
    m_viewCar->updateDirection(m_model->getCarDir());
}

void View::addModel(Race *m) {
	this->m_model = m;
}

sf::RenderWindow* View::getWindow()
{
	return m_window;
}

void View::initializeRace(std::vector<Segment> segments){
    for(auto segment : segments){
        //m_viewTrack->addSegment(std::move(viewSegment));
    }
}

void View::display()
{
	m_window->clear(sf::Color::Blue);
	m_viewTrack->display();
	m_viewCar->display();
}

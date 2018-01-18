//
// Created by Culring on 2018-01-08.
//

#include "View.h"
#include <iostream>

View::View() : 
	m_window(new sf::RenderWindow(sf::VideoMode(800, 600), "Bylena3:<"))
{
	m_viewCar = new ViewCar(m_window);
}

View::~View()
{
	delete m_window;
	delete m_viewCar;
}

void View::updateCar(){
    m_viewCar->updatePosition(m_model->getCarX(), m_model->getCarY());
    m_viewCar->updateDirection(m_model->getCarDir());
}

sf::RenderWindow* View::getWindow()
{
	return m_window;
}

void View::initializeRace(std::vector<Segment> segments){
    for(auto segment : segments){
        ViewSegment viewSegment;
        m_viewTrack->addSegment(std::move(viewSegment));
    }
}

void View::display()
{
	m_window->clear(sf::Color::Blue);
	m_viewCar->display();
}

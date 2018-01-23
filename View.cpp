//
// Created by Culring on 2018-01-08.
//

#include "View.h"

View::View() : 
	m_window(new sf::RenderWindow(sf::VideoMode(1280, 720), "Racing game")), m_model(nullptr), m_viewCar(nullptr), m_viewTrack(nullptr)
{
	resetView();
	initMenuElements();
}

View::~View()
{
	delete m_viewCar;
	delete m_viewTrack;
	delete m_window;
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

ViewTrack *View::getTrack() {
	return m_viewTrack;
}

void View::gameMode() {
	m_viewCar = new ViewCar(m_window);
	m_viewTrack = new ViewTrack(m_window);
	m_viewCar->updatePosition(m_viewTrack->getPositionOfFirstSegment().x,  m_viewTrack->getPositionOfFirstSegment().y);
	sf::View view = m_window->getDefaultView();
	view.zoom(2.5f);
//	view.zoom(1.5f);
	view.setCenter(m_viewCar->getPosition().x, m_viewCar->getPosition().y);
	m_window->setView(view);
}

void View::endGame() {
	delete m_viewCar;
	delete m_viewTrack;
}

void View::initializeRace(std::vector<Segment> segments){
    for(auto segment : segments){
        //m_viewTrack->addSegment(std::move(viewSegment));
    }
}

void View::displayMenu()
{
	m_window->clear(sf::Color::Black);
	m_window->draw(background);
	m_window->draw(playerModeOption);
	m_window->draw(aiModeOption);
}

void View::display()
{
	m_window->clear(sf::Color(200, 200, 255));
	m_viewTrack->display();
	m_viewCar->display();
}

void View::resetView() {
	sf::View view = m_window->getDefaultView();
	view.zoom(2.5f);
	view.setCenter(0, 0);
	m_window->setView(view);
}

void View::initMenuElements() {
	if(!menuTexture.loadFromFile(BACKGROUND_TEXTURE, BACKGROUND_RECTANGLE)) {
		throw std::exception();
	}

	background.setTexture(menuTexture);
	background.setOrigin(640, 360);
	background.scale(2.0f, 2.0f);

	if(!font.loadFromFile(".\\fonts\\arial.ttf")) {
		throw std::exception();
	}

	playerModeOption.setFont(font);
	playerModeOption.setString("Press [1] to start Player mode");
	playerModeOption.setCharacterSize(80);
	playerModeOption.setFillColor(sf::Color::White);
	playerModeOption.setOrigin(playerModeOption.getLocalBounds().width/2, -500);

	aiModeOption.setFont(font);
	aiModeOption.setString("Press [2] to start AI mode");
	aiModeOption.setCharacterSize(80);
	aiModeOption.setFillColor(sf::Color::White);
	aiModeOption.setOrigin(aiModeOption.getLocalBounds().width/2, -600);
}

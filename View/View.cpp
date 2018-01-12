//
// Created by Culring on 2018-01-08.
//

#include "View.h"

void View::addModel(Race &model){
    m_model = model;
}

void View::updateCar(){
    m_viewCar.updatePosition(m_model.getCarX(), m_model.getCarY());
    m_viewCar.updateDirection(m_model.getCarDir());
}

void View::initializeRace(std::vector<Segment> segments){
    for(auto segment : segments){
        ViewSegment viewSegment;
        m_viewTrack.addSegment(viewSegment);
    }
}

int main()
{
    sf::RenderWindow okno( sf::VideoMode( 320, 240 ), "Kurs SFML 2.0 - http://cpp0x.pl" );
    sf::Clock stoper;
    while( okno.isOpen() )
    {
        sf::Event event;
        while( okno.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                okno.close();

        } //while
        okno.clear();

        sf::CircleShape ksztalt( std::sin( stoper.getElapsedTime().asSeconds() ) * okno.getSize().y / 8 + okno.getSize().y / 4 );
        ksztalt.setOrigin( sf::Vector2f( ksztalt.getRadius(), ksztalt.getRadius() ) );
        ksztalt.setPosition( okno.getSize().x / 2.0f, okno.getSize().y / 2.0f );
        ksztalt.setFillColor( sf::Color::Yellow );
        okno.draw( ksztalt );

        okno.display();
    } //while
    return 0;
}
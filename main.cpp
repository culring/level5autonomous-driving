//
// Created by Culring on 2018-01-04.
//

#include "Controller.h"

int main(void) {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Kurs SFML 2.0 - http://cpp0x.pl" );
	Controller controller(window);
	//Model model;
	//View view;
	//model.addView(view);
	//view.addmodel(model);
	//Controller c(model, view);
	controller.menu();
}

//
// Created by Culring on 2018-01-04.
//

#include "Controller.h"
#include "View.h"

int main(void) {
	Controller controller;
	//Model model;
	//View view;
	//model.addView(view);
	//view.addmodel(model);
	//Controller c(model, view);
	controller.menu();
	std::cout << "end main" << std::endl;
	controller.~Controller();
	return 0;
}

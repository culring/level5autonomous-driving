//
// Created by Culring on 2018-01-08.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_VIEW_H
#define LEVEL5AUTONOMOUS_DRIVING_VIEW_H

#include "../Model.h"

class View {
    Race m_model;

public:
    void addModel(Race model);
    void initializeRace();
    void updateCar();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_VIEW_H
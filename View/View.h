//
// Created by Culring on 2018-01-08.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_VIEW_H
#define LEVEL5AUTONOMOUS_DRIVING_VIEW_H

#include <vector>
#include "../Model.h"
#include "ViewCar.h"
#include "ViewTrack.h"
#include <SFML/Graphics.hpp>
#include <cmath>

class View {
    // view variables
    ViewCar m_viewCar;
    ViewTrack m_viewTrack;
    // model
    Race &m_model;

public:
    void addModel(Race &model);
    void initializeRace(std::vector<Segment> segments);
    void updateCar();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_VIEW_H
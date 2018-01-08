//
// Created by Culring on 2018-01-08.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_VIEW_H
#define LEVEL5AUTONOMOUS_DRIVING_VIEW_H

class View {
    Model m_model;

public:
    void addModel(Model model);
    void initializeRace();
    void updateCar();
};

#endif //LEVEL5AUTONOMOUS_DRIVING_VIEW_H
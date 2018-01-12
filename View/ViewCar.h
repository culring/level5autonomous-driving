//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_CAR_H
#define LEVEL5AUTONOMOUS_DRIVING_CAR_H

class ViewCar {
    // current car's position
    float m_positionX, m_positionY;
    // current car's orientation
    float m_direction;

    void move();

public:
    void updatePosition(float positionX, float positionY);
    void updateDirection(float direction);
};

#endif //LEVEL5AUTONOMOUS_DRIVING_CAR_H

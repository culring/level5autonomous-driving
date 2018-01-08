//
// Created by Culring on 2018-01-04.
//

#ifndef LEVEL5AUTONOMOUS_DRIVING_CAR_H
#define LEVEL5AUTONOMOUS_DRIVING_CAR_H

class Car {
    // current car's position
    float m_positionX, m_positionY;
    // current car's speed
    float m_speed;
    // current car's steering value
    float m_steering;

    void move();

public:
    Car();
    ~Car();

    void updatePosition(float positionX, float positionY);
    void setSpeed(float speed);
    void setSteering(float steering);
};

#endif //LEVEL5AUTONOMOUS_DRIVING_CAR_H

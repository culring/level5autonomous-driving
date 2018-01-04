//
// Created by Culring on 2018-01-04.
//

#include "Car.h"

namespace view{
    Car::Car()
    {

    }
    Car::~Car()
    {

    }

    void Car::updatePosition(float positionX, float positionY)
    {
        m_positionX = positionX;
        m_positionY = positionY;
    }

    void Car::setSpeed(float speed)
    {
        m_speed = speed;
    }

    void Car::setSteering(float steering)
    {
        m_steering = steering;
    }
}
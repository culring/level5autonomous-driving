//
// Created by Culring on 2018-01-04.
//

#include "ViewCar.h"

ViewCar::ViewCar()
{

}
ViewCar::~ViewCar()
{

}

void ViewCar::updatePosition(float positionX, float positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
}

void ViewCar::setSpeed(float speed)
{
    m_speed = speed;
}

void ViewCar::setSteering(float steering)
{
    m_steering = steering;
}
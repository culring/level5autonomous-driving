//
// Created by Culring on 2018-01-04.
//

#include "ViewCar.h"

void ViewCar::updatePosition(float positionX, float positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
}

void ViewCar::updateDirection(float direction){
    m_direction = direction;
}
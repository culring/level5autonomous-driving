#ifndef TEXTURES_H
#define TEXTURES_H

const std::string TEXTURES_DIRECTORY = R"(.\sprites\)";
const std::string CAR_TEXTURES_DIRECTORY = TEXTURES_DIRECTORY + "cars_mini.png";
const std::string ROAD_TEXTURES_DIRECTORY = TEXTURES_DIRECTORY + "Road_test.png";

const sf::Rect<int> CAR_RECTANGLE(0, 0, 179, 306);
const sf::Rect<int> STRAIGHT_ROAD_RECTANGLE(375, 655, 705, 1024);
const sf::Rect<int> CORNER_ROAD_RECTANGLE(218, 2269, 862, 862);

#endif

/*
Common.hpp - common (global) functions
*/

#ifndef common_hpp_
#define common_hpp_

#include <cstdlib>
#include <ctime>
#include "SFML/Graphics.hpp"

void InitRandom();
int RandomNumber(int min, int max);
float RandomNumber(float min, float max);
sf::Vector2f Center(sf::Rect<float> rect);

#endif
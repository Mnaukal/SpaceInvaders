#include "Common.hpp"

void InitRandom() {
	std::srand(std::time(0));
}

int RandomNumber(int min, int max)
{
	return (std::rand() % (max - min)) + min;
}

sf::Vector2f Center(sf::Rect<float> rect)
{
	return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

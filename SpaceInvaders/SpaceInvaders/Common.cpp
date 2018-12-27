#include "Common.hpp"

void InitRandom() {
	std::srand(std::time(0));
}

int RandomNumber(int min, int max)
{
	return (std::rand() % (max - min)) + min;
}

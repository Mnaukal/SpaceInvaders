#include "EnemyWave.hpp"

EnemyWave::Type EnemyWave::GetRandomSpawnType()
{
	int type_count = 0;
	if (spawn_simple) type_count++;
	if (spawn_moving) type_count++;
	if (spawn_shooting) type_count++;

	int selected = RandomNumber(0, type_count);

	if (spawn_simple)
		if (selected == 0)
			return Type::Simple;
		else
			selected--;
	if (spawn_moving)
		if (selected == 0)
			return Type::Moving;
		else
			selected--;
	if (spawn_shooting)
		if (selected == 0)
			return Type::Shooting;
		else
			selected--;

	return Type::Simple; // TODO maybe throw exception, should not happen
}

float EnemyWave::GetRandomSpawnTime()
{
	return RandomNumber(min_time, max_time);
}

/*
EnemyWave.hpp - data holder for waves of enemies
*/

#ifndef wave_hpp_
#define wave_hpp_

#include "Common.hpp"

class EnemyWave  {
public:
	enum class Type {
		Simple = 0, Moving = 1, Shooting = 2
	};
	int count;
	float min_time, max_time;
	bool spawn_simple, spawn_moving, spawn_shooting;
	Type GetRandomSpawnType();
	float GetRandomSpawnTime();
};
#endif
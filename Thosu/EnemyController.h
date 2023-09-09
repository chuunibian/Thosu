#pragma once

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

constexpr float SECOND_IN_MINUTE = 60.0;

using namespace sf;

class EnemyController
{
private:
	//EnemyAnimation enemy_animation;
	Clock timer;
	//make accel decell for enemyt movement

	float stage_max_time = 3 * SECOND_IN_MINUTE;
public:

	EnemyController();
	~EnemyController();
};


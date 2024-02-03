#pragma once

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include "EnemyAnimation.h"

constexpr float SECOND_IN_MINUTE = 60.0;

using namespace sf;

class EnemyController
{
private:
	//make accel decell for enemyt movement

public:
	EnemyAnimation enemy_animation;

	EnemyController();
	~EnemyController();

	void update();
	void render(RenderTarget& target);
};


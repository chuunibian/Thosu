#pragma once

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include "EnemyAnimation.h"

constexpr float SECOND_IN_MINUTE = 60.0;

using namespace sf;

class EnemyController
{
private:
	EnemyAnimation enemy_animation;
	//make accel decell for enemyt movement

public:
	EnemyController();
	~EnemyController();

	void update();
	void render(RenderTarget& target);
};


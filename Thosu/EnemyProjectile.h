#pragma once
#include <SFML/Graphics.hpp>
#include "GameEnums.h"

using namespace sf;

class EnemyProjectile
{
public:
	EnemyProjectile(sf::Texture *texture, Vector2f velocity, Vector2f position, IntRect rect);
	~EnemyProjectile();

	void update(float delta_time, stage stage_state);
	void update(float delta_time);
	//void updateWithAccel(float delta_time);
	void rotate(float delta_time);
	Sprite* getProjectileSprite();
private:
	Sprite sprite;
	Vector2f velocity;

	int fast_switch_counter = 0;
	float acceleration_counter = .001;

	void initializeVariables();
};


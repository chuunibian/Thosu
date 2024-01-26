#pragma once
#include <cstdlib>
#include "Enemy.h"

constexpr auto ENEMY_SPRITE_DIMENSION_W = 407.f / 4;
constexpr auto ENEMY_SPRITE_DIMENSION_H = 132.f;
constexpr auto OFFSET_CONSTANT = 2;
constexpr auto ENEMY_POSITION_BOUNDS_H = 550;
constexpr auto ENEMY_POSITION_BOUNDS_W = 550;
constexpr auto PRECISION_ERROR = 3.0;




class EnemyAnimation
{
private:
	Enemy enemy;
	Sprite enemy_sprite;
	Clock clock_animation;
	Clock clock_movement;
	IntRect enemy_sprite_frame;
	Vector2f random_target_position;

	float animation_delay;
	int movement_delay;
	float movement_speed = 4;
	float enemy_sprite_scale;
	bool movement_done_flag = false;

	void initializeVariables();
	void initEnemyFrame();
	void initEnemySprite();
	void updateEnemyPosition();
	void updateEnemyAnimation();

public:
	EnemyAnimation();
	~EnemyAnimation();

	void render(RenderTarget& target);
	void update();
};


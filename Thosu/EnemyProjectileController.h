#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "EnemyProjectile.h"

using namespace sf;

//these should be capitalized
constexpr auto max_sector_projectiles = 3000;
constexpr auto max_2nd_sector_projectiles = 500;
constexpr auto total_2nd_projectiles = max_2nd_sector_projectiles * 2;
constexpr auto total_projectiles = max_sector_projectiles * 16;
constexpr double red_ball_wave_time = 0.1;
constexpr double blue_ball_wave_time = 115;
constexpr double purple_ball_wave_time = 50;
constexpr float game_window_height = 1000;
constexpr float game_window_width = 750;
constexpr double radius = 20;
constexpr double Pi = 3.14159265358979323846;

enum stage {STAGE_1, STAGE_2, STAGE_3, STAGE_4, STAGE_5};

class EnemyProjectileController
{
public: 
	EnemyProjectileController();
	~EnemyProjectileController();

	void update(float dt, Vector2f enemy_position);
	void render(RenderTarget& target);

private:

	Transform transform;
	RenderStates state;
	EnemyProjectile* projectiles[total_projectiles];
	EnemyProjectile* projectiles_2nd[total_2nd_projectiles];
	VertexArray sectors;
	VertexArray sectors_2;
	Texture chromatic_ball_projectile;
	Texture blue_knife_projectile;
	Clock stage_timer;

	stage stage_state;

	double red_ball_time_counter;
	double blue_ball_time_counter;
	double purple_ball_time_counter;
	double blue_knife_time_counter;
	double bg_laser_time_counter;
	float rand_y;
	int wave_switch1;
	int wave_switch2;
	int wave_switch3;
	int red_bullet_count;
	int blue_bullet_count;
	int purple_bullet_count;
	int blue_knife_bullet_count;
	bool negative_flip_flag;

	void initializeVariables();
	void initializeTextures();

	void addProjectileToSector(VertexArray* general_sector, EnemyProjectile* bul, int i);
	void updateSectorProjectilePosition(float dt);
	void updateProjectilePattern(float dt, Vector2f enemy_position);
};


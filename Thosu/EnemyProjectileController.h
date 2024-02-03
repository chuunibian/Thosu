#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "EnemyProjectile.h"

constexpr auto max_sector_projectiles = 2500;
constexpr auto max_2nd_sector_projectiles = 500;
constexpr auto total_2nd_projectiles = max_2nd_sector_projectiles * 2;
constexpr auto total_projectiles = max_sector_projectiles * 16;
constexpr double red_ball_wave_time = 0.3;
constexpr double blue_ball_wave_time = 20;
constexpr double purple_ball_wave_time = 40;
constexpr float game_window_height = 1000;
constexpr float game_window_width = 750;
constexpr double radius = 20;
constexpr double Pi = 3.14159265358979323846;

using namespace sf;

class EnemyProjectileController
{
public: 
	EnemyProjectileController();
	~EnemyProjectileController();

	void update();
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

	double red_ball_time_counter;
	double blue_ball_time_counter;
	double purple_ball_time_counter;
	double blue_knife_time_counter;

	int wave_switch1;
	int wave_switch2;
	int wave_switch3;

	int red_bullet_count;
	int blue_bullet_count;
	int purple_bullet_count;
	int blue_knife_bullet_count;


	void initializeVariables();
	void initializeTextures();

	void addProjectileToSector(VertexArray* general_sector, EnemyProjectile* bul, int i);
	void updateSectorProjectilePosition();
	void updateProjectilePattern();
};


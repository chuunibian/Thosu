#pragma once

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

#define INITIAL_PROJECTILE_SPEED 0.0;
using namespace sf;

class PlayerProjectile
{
private: 
	Sprite player_projectile_sprite;

	Vector2f projectile_direction;

	float movementSpeed = INITIAL_PROJECTILE_SPEED;

public:

	PlayerProjectile(); //Default constructor currently no purpose
	PlayerProjectile(Texture* projectile_texture, float origin_position_X, float origin_position_Y, float direction_X, float direction_Y, float movement_speed);
	~PlayerProjectile();

	//Acessors
	const FloatRect getPlayerProjectileBounds() const; //will be used for culling

	
	void update();
	void render();

};


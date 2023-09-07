#pragma once

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

constexpr auto INITIAL_PROJECTILE_SPEED = 0.0;
constexpr float PLAYER_PROJ_SCALE = 0.7; 

using namespace sf;

class PlayerProjectile
{
private:
	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	/////////////////////////////////////////
	Sprite player_projectile_sprite;
	Vector2f projectile_direction;
	
	/////////////////////////////////////////
	// primitive instance variables for projectile physics
	/////////////////////////////////////////
	float movementSpeed = INITIAL_PROJECTILE_SPEED;

public:
	/* ======== Con/Decon ======== */

	/////////////////////////////////////////
	// Default constructor currently no purpose
	/////////////////////////////////////////
	PlayerProjectile();

	/////////////////////////////////////////
	// Overloaded constructor that takes in texture
	// origin positions directions and speed
	// used as a initializer for PProj creation
	/////////////////////////////////////////
	PlayerProjectile(Texture* projectile_texture, float origin_position_X, float origin_position_Y, float direction_X, float direction_Y, float movement_speed);

	/////////////////////////////////////////
	// Deconstructor
	/////////////////////////////////////////
	~PlayerProjectile();

	/* ======== Accessors ======== */

	////////////////////////////////////////
	// public method that returns the global bounds
	// as a float rect constant. Applications can
	// be used in player projectile culling
	// 
	// @return this->player_projectile_sprite global bounds
	/////////////////////////////////////////
	const FloatRect getPlayerProjectileBounds() const;

	////////////////////////////////////////
	// Returns the player's origin as a Vector2f
	// 
	// @return this->player_projectile_sprite origin
	/////////////////////////////////////////
	Vector2f getPlayerOrigin();

	/* ======== Update/Render ======== */

	////////////////////////////////////////
	// Updates internal logic of the player projectile
	// object. Mainly logic and state of 
	// this->player_projectile_sprite will be changed
	/////////////////////////////////////////
	void update();
	void render(RenderTarget* target);

};


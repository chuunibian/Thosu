#pragma once
#include "PlayerAnimation.h"
#include "PlayerProjectile.h"

constexpr auto PLAYER_ATTACK_COOLDOWN_MAX = 3.f;
constexpr auto ATTACK_COOLDOWN_TIMING_INCREMENT = .5f;
constexpr float zero_C = 0;

class PlayerController
{
private:
	/////////////////////////////////////////
	// Compositional Objects
	// 
	/////////////////////////////////////////
	PlayerAnimation* player_animation;

	/////////////////////////////////////////
	// Primitive variables that help with the 
	// mathemetical logic, timing, and physics 
	// of movement.
	// 
	/////////////////////////////////////////
	bool moving_right_flag;
	bool moving_left_flag;
	float velocity;
	float attack_cd_time;
	float attack_cd_max;

	/////////////////////////////////////////
	// Standard Template datastructures that hold
	// objects required for player to function like
	// projectiles and textures
	// 
	/////////////////////////////////////////
	std::map<std::string, Texture*> player_projectile_textures; //Bullet storing datastructures although a bit out of place not sure if it adheres to OOP
	std::vector<PlayerProjectile*> player_projectiles;

	/* ======== Initializers ======== */
	/////////////////////////////////////////
	// Initializes a variety of variables important
	// to state of being or numerical logic
	// 
	/////////////////////////////////////////
	void initVariables();

	/////////////////////////////////////////
	// Initializes the player projectile texture 
	// using the map datastructure
	// 
	/////////////////////////////////////////
	void initPlayerProjectileTexture();
	/* =============================== */

	/////////////////////////////////////////
	// Updates the player animation sprites location
	// to mimic movement on the screen
	// 
	/////////////////////////////////////////
	void updatePlayerMovement();

	/////////////////////////////////////////
	// Prevents the player animation from going out of the 
	// window that it is bound to
	// 
	// @param screen_width
	//		width of the bounded window
	// @param screen_height
	//		height of the bounded window
	// 
	/////////////////////////////////////////
	void updatePlayerWindowCollision(float& screen_width, float& screen_height);

	/////////////////////////////////////////
	// Resets or modifies the projectile shooting timer
	// 
	/////////////////////////////////////////
	void updateCooldown();

	/////////////////////////////////////////
	// Updates each of the player projectile objects
	// in the PProj vector.
	// 
	/////////////////////////////////////////
	void updatePlayerProjectiles();

	/////////////////////////////////////////
	// Checks if the player projectile is off the window bounds
	// if so it deletes them from the PProj vector
	// 
	/////////////////////////////////////////
	void updatePlayerProjectilesCulling();

	/////////////////////////////////////////
	// Checks if the cooldown timer is enough to 
	// fire again, this controls the firerate of 
	// the player projectiles
	// 
	/////////////////////////////////////////
	bool canAttack();

public:
	/* ======== Con/Decon ======== */
	///////////////////////////////////////////////
	// Default constructor
	// 
	///////////////////////////////////////////////
	PlayerController();

	///////////////////////////////////////////////
	// Default deconstructor
	// 
	///////////////////////////////////////////////
	~PlayerController();
	/* =========================== */

	/* ======== Update/Render ======== */
	/////////////////////////////////////////////
	// Updates internal logic of the player projectile
	// object. State of the sprite animation, projectile
	// and boundaries will be updated.
	// 
	// Calls: 	updateCooldown();
	//          player_animation->update();
	//          updatePlayerMovement();
	//          updatePlayerWindowCollision(screen_height, screen_width);
	//          updatePlayerProjectiles();
	//			updatePlayerProjectilesCulling();
	// @param screen_width
	//		window width pixel size
	// @param screen_height
	//		window height pixel size
	// 
	//////////////////////////////////////////////
	void update(float screen_width, float screen_height);

	///////////////////////////////////////////////
	// Renders internal logic of the whole player animation
	// object graphically to the render target window.
	// This render encompasses multiple renders from
	// composed classes
	// 
	// @param target
	//		window to be rendered on
	// 
	///////////////////////////////////////////////
	void render(RenderTarget& target);
	/* =============================== */
};


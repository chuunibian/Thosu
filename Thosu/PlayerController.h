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

	void initVariables();
	void initPlayerProjectileTexture();

	void updatePlayerMovement();
	void updatePlayerWindowCollision(float& screen_width, float& screen_height);
	void updateCooldown();
	void updatePlayerProjectiles();
	void updatePlayerProjectilesCulling();

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


#pragma once
#include "PlayerAnimation.h"
#include "PlayerProjectile.h"

#define PLAYER_ATTACK_COOLDOWN_MAX 5.f
#define ATTACK_COOLDOWN_TIMING_INCREMENT .3f

class PlayerController
{
private:
	PlayerAnimation* player_animation;

	bool moving_right_flag;
	bool moving_left_flag;
	float velocity;
	float attack_cd_time;
	float attack_cd_max;
	const float zero_C = 0; //const term for zero

	//Bullet storing datastructures although a bit out of place not sure if it adheres to OOP
	std::map<std::string, Texture*> player_projectile_textures;
	std::vector<PlayerProjectile*> player_projectiles;

	void initVariables();
	void updatePlayerMovement();
	bool canAttack();
	void updateCooldown();

public:
	PlayerController();
	~PlayerController();

	void update();
	void render(RenderTarget& target);
};


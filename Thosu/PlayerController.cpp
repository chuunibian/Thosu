#include "PlayerController.h"

void PlayerController::initVariables()
{
	player_animation = new PlayerAnimation;
	//moving_left_flag = false;
	//moving_right_flag = false;
	attack_cd_time = PLAYER_ATTACK_COOLDOWN_MAX;
	attack_cd_max = PLAYER_ATTACK_COOLDOWN_MAX;
}

void PlayerController::initPlayerProjectileTexture()
{
	player_projectile_textures["BULLET"] = new Texture();
	player_projectile_textures["BULLET"]->loadFromFile("Textures/playerbulletspriteT2.png");
}

PlayerController::PlayerController()
{
	initVariables();
	initPlayerProjectileTexture();
}

PlayerController::~PlayerController()
{
}

void PlayerController::updatePlayerMovement()
{
	if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::D)) {
			player_animation->changePlayerState(PLAYER_ANIMATION_STATES::IDLE);
	}
	else {

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player_animation->move(0.f, -3.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player_animation->move(0.f, 3.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player_animation->changePlayerState(PLAYER_ANIMATION_STATES::LEFT);
			player_animation->move(-3.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player_animation->changePlayerState(PLAYER_ANIMATION_STATES::RIGHT);
			player_animation->move(3.f, 0.f);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && canAttack()) { //last for a reason? since it will get the player animation bounds
		player_projectiles.push_back(new PlayerProjectile(player_projectile_textures["BULLET"], player_animation->getPlayerPosition().x + player_animation->getPlayerBounds().width / 7.f,
			player_animation->getPlayerPosition().y - 20,
			0.f, -1.f, 21.f));
	}
}

bool PlayerController::canAttack()
{ //avoiding multiple returns
	bool can_attack_flag = false;
	if (attack_cd_time >= attack_cd_max) {
		attack_cd_time = zero_C;
		can_attack_flag = true;
	}
	return can_attack_flag;
}

void PlayerController::updateCooldown()
{
	if (attack_cd_time < attack_cd_max) {
		attack_cd_time += ATTACK_COOLDOWN_TIMING_INCREMENT;
	}
}

void PlayerController::updatePlayerProjectiles()
{
	unsigned int counter = zero_C;
	for (auto* projectile : player_projectiles) {
		projectile->update(); //update the bullet
	}

}

void PlayerController::update()
{
	updateCooldown();
	player_animation->update();
	updatePlayerMovement();
	updatePlayerProjectiles();
}

void PlayerController::render(RenderTarget& target)
{
	//target.draw(player_animation->getSprite()); //you can also just call render from player animation?? Imma do it below
	player_animation->render(target);
	for (auto* projectile : player_projectiles) {
		projectile->render(&target);
	}
}

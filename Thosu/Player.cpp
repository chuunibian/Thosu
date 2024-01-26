#include "Player.h"

void Player::initVariables()
{
}

void Player::initSprite()
{
	player_sprite.setTexture(player_sprite_texture);
}

void Player::initTexture()
{
	bool sprite_load_flag = player_sprite_texture.loadFromFile("Textures/rem.png");
	if (!sprite_load_flag) {
		std::cout << "Player texture failed" << "\n";
	}
	else {
		std::cout << "Texture loaded successfully" << "\n";
	}
}

Player::Player()
{
	initVariables();
	initTexture();
	initSprite();
}

Player::~Player()
{
}

Sprite Player::getPlayerSprite()
{
	return player_sprite;
}


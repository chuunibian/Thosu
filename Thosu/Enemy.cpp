#include "Enemy.h"

void Enemy::initializeVariables()
{
}

void Enemy::initSprite()
{
	enemy_sprite.setTexture(enemy_texture);
}

void Enemy::initTexture()
{
	bool sprite_load_flag = enemy_texture.loadFromFile("Textures/thosuE1.png");
	if (!sprite_load_flag) {
		std::cout << "Enemy texture failed" << "\n";
	}
	else {
		std::cout << "Enemy Texture loaded successfully" << "\n";
	}
}

Enemy::Enemy()
{
	initializeVariables();
	initSprite();
	initTexture();
}

Enemy::~Enemy()
{
}

Sprite Enemy::getEnemySprite()
{
	return enemy_sprite;
}

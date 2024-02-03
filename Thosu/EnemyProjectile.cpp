#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(sf::Texture* texture, Vector2f velocity, Vector2f position, IntRect rect)
{
	this->velocity = velocity;
	sprite.setTexture(*texture);
	sprite.setTextureRect(rect);
	sprite.setPosition(position);
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::update(float delta_time)
{
	sprite.setPosition(sprite.getPosition().x + delta_time * velocity.x, sprite.getPosition().y + delta_time * velocity.y);
}

Sprite* EnemyProjectile::getProjectileSprite()
{
	return &sprite; //return address of which the sprite is at
}

void EnemyProjectile::initializeVariables()
{
}

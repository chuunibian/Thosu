#include "PlayerProjectile.h"


PlayerProjectile::PlayerProjectile()
{
}

PlayerProjectile::PlayerProjectile(Texture* projectile_texture, float origin_position_X, float origin_position_Y, float direction_X, float direction_Y, float movement_speed)
{
	player_projectile_sprite.setTexture(*projectile_texture);
	player_projectile_sprite.setScale(PLAYER_PROJ_SCALE, PLAYER_PROJ_SCALE);
	player_projectile_sprite.setPosition(origin_position_X, origin_position_Y);
	projectile_direction.x = direction_X;
	projectile_direction.y = direction_Y;
	movementSpeed = movement_speed;
}

PlayerProjectile::~PlayerProjectile()
{
}

const FloatRect PlayerProjectile::getPlayerProjectileBounds() const
{
	return player_projectile_sprite.getGlobalBounds();
}

Vector2f PlayerProjectile::getPlayerOrigin()
{
	return player_projectile_sprite.getOrigin();
}

void PlayerProjectile::update()
{
	player_projectile_sprite.move(movementSpeed * projectile_direction);
}

void PlayerProjectile::render(RenderTarget* target)
{
	target->draw(player_projectile_sprite);
}

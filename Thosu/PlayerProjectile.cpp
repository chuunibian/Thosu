#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile()
{
}

PlayerProjectile::PlayerProjectile(Texture* projectile_texture, float origin_position_X, float origin_position_Y, float direction_X, float direction_Y, float movement_speed)
{
	player_projectile_sprite.setPosition(origin_position_X, origin_position_Y);
}

PlayerProjectile::~PlayerProjectile()
{
}

const FloatRect PlayerProjectile::getPlayerProjectileBounds() const
{
	return player_projectile_sprite.getGlobalBounds();
}

void PlayerProjectile::update()
{
}

void PlayerProjectile::render()
{
}

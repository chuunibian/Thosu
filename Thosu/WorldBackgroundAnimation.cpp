#include "WorldBackgroundAnimation.h"

void WorldBackgroundAnimation::initVariables()
{
}

void WorldBackgroundAnimation::initBackgroundSprite()
{
	background_sprite = world_background.getBackgroundSprite();
}

void WorldBackgroundAnimation::initBackgroundFrame()
{
	background_sprite_frame = IntRect(0, 0, WORLD_SPRITE_FRAME_DIMENSION_W, WORLD_SPRITE_FRAME_DIMENSION_H);
	background_sprite.setTextureRect(background_sprite_frame);
}

void WorldBackgroundAnimation::initBackgroundAnimation()
{
	animation_timer.restart();
}

void WorldBackgroundAnimation::updateAnimation()
{
	if (background_sprite_frame.left > 2497 - 750) { //for those numbers make it into cosntexpr
		background_sprite_frame.left = 55;
	}
	else {
		background_sprite_frame.left += BACKGROUND_FRAME_INCREMENT;
	}
	background_sprite.setTextureRect(background_sprite_frame);
}

WorldBackgroundAnimation::WorldBackgroundAnimation()
{
	initBackgroundAnimation();
	initBackgroundFrame();
	initBackgroundSprite();
}

WorldBackgroundAnimation::~WorldBackgroundAnimation()
{
}

void WorldBackgroundAnimation::update()
{
	updateAnimation();
}

void WorldBackgroundAnimation::render(RenderTarget& target)
{
	target.draw(background_sprite);
}

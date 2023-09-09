#pragma once

#include "WorldBackground.h"

constexpr auto WORLD_SPRITE_FRAME_DIMENSION_H = 1000;
constexpr auto WORLD_SPRITE_FRAME_DIMENSION_W = 750;
constexpr auto BACKGROUND_FRAME_INCREMENT = 1;

class WorldBackgroundAnimation
{
private:
	WorldBackground world_background;

	Sprite background_sprite;
	Clock animation_timer;
	IntRect background_sprite_frame;

	float animation_interval_delay;

	void initVariables();
	void initBackgroundSprite();
	void initBackgroundFrame();
	void initBackgroundAnimation();
	void updateAnimation();
public:
	WorldBackgroundAnimation();
	~WorldBackgroundAnimation();

	void update();
	void render(RenderTarget& target);

};


#include "WorldBackground.h"

void WorldBackground::initVariables()
{
}

void WorldBackground::initSprite()
{
	world_background_sprite.setTexture(world_background_texture);
}

void WorldBackground::initTexture()
{
	bool sprite_load_flag = world_background_texture.loadFromFile("Textures/thosustg1.jpg");
	if (!sprite_load_flag) {
		std::cout << "World texture failed" << "\n";
	}
	else {
		std::cout << "World Texture loaded successfully" << "\n";
	}
}

Sprite WorldBackground::getBackgroundSprite()
{
	return world_background_sprite;
}

WorldBackground::WorldBackground()
{
	initVariables();
	initTexture();
	initSprite();
}

WorldBackground::~WorldBackground()
{
}

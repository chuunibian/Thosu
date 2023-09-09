#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>

using namespace sf;

class WorldBackground
{
private:
	Sprite world_background_sprite;
	Texture world_background_texture;

	//Can use vector to store mult sprite and init it that way for multi stages

	void initVariables();
	void initSprite();
	void initTexture();
public:
	Sprite getBackgroundSprite();

	WorldBackground();
	~WorldBackground();

};


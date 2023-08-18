#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	//SFML composition objects
	Sprite player_sprite;
	Texture player_sprite_texture;

	//Initialization Functions
	void initVariables();
	void initSprite();
	void initTexture();

public:
	//Con Decon
	Player();
	~Player();

	//Accessors
	Sprite getPlayerSprite();

};


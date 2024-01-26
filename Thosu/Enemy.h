#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Enemy
{
private:
	Sprite enemy_sprite;
	Texture enemy_texture;

	void initializeVariables();
	void initSprite();
	void initTexture();
public:
	Enemy();
	~Enemy();

	Sprite getEnemySprite();
};


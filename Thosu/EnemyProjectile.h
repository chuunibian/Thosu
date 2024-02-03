#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class EnemyProjectile
{
public:
	EnemyProjectile(sf::Texture *texture, Vector2f velocity, Vector2f position, IntRect rect);
	~EnemyProjectile();

	void update(double delta_time);
	Sprite* getProjectileSprite();
private:
	Sprite sprite;
	Vector2f velocity;
};


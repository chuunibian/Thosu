#pragma once

#include<SFML/Graphics.hpp>

using namespace sf;

class CollisionController
{
private:
	
	
public:
	CollisionController();
	~CollisionController();

	void updatePlayerCollision(Sprite& player_sprite); //pass in as pointer?

	void update();
	void render(RenderWindow& target);

};


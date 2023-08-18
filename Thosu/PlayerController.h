#pragma once
#include "PlayerAnimation.h"

class PlayerController
{
private:
	PlayerAnimation* player_animation;

	bool moving_right_flag;
	bool moving_left_flag;
	float velocity;

	void initVariables();

	void updatePlayerMovement();

public:
	PlayerController();
	~PlayerController();

	void update();
	void render(RenderTarget& target);
};


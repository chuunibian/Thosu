#include "PlayerController.h"

void PlayerController::initVariables()
{
	player_animation = new PlayerAnimation;
	moving_left_flag = false;
	moving_right_flag = false;
}

PlayerController::PlayerController()
{
	initVariables();
}

PlayerController::~PlayerController()
{
}

void PlayerController::updatePlayerMovement()
{
	//moving_left_flag = false; //initially set both flags false to go into idle?
	//moving_right_flag = false;

	if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::D)) {
			player_animation->changePlayerState(PLAYER_ANIMATION_STATES::IDLE);
	}
	else {

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player_animation->move(0.f, -3.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player_animation->move(0.f, 3.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			moving_left_flag = true;
			moving_right_flag = false;
			player_animation->changePlayerState(PLAYER_ANIMATION_STATES::LEFT);
			player_animation->move(-3.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player_animation->changePlayerState(PLAYER_ANIMATION_STATES::RIGHT);
			moving_left_flag = false;
			moving_right_flag = true;
			player_animation->move(3.f, 0.f);
		}
	}
}

void PlayerController::update()
{
	updatePlayerMovement();
	player_animation->update();
}

void PlayerController::render(RenderTarget& target)
{
	target.draw(player_animation->getSprite());
}

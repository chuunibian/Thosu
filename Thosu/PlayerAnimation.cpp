#include "PlayerAnimation.h"

void PlayerAnimation::initVariables()
{
	animation_state = PLAYER_ANIMATION_STATES::IDLE;
	animation_interval_delay = .185f; //Optimize?
	idle_animation_switch = true;
	
}

void PlayerAnimation::initPlayerSprite()
{
	player_sprite = player.getPlayerSprite();
}

void PlayerAnimation::initPlayerFrame()
{
	player_sprite_frame = IntRect(3, 0, SPRITE_FRAME_DIMENSION_W, SPRITE_FRAME_DIMENSION_H);
	player_sprite.setTextureRect(player_sprite_frame);
	player_sprite.setScale(PLAYER_SPRITE_SCALE, PLAYER_SPRITE_SCALE);

}

void PlayerAnimation::initPlayerAnimation()
{
	animation_timer.restart();
}

PlayerAnimation::PlayerAnimation()
{
	initVariables();
	initPlayerSprite();
	initPlayerFrame();
	initPlayerAnimation();
}

PlayerAnimation::~PlayerAnimation()
{
}

void PlayerAnimation::changePlayerState(PLAYER_ANIMATION_STATES state)
{
	animation_state = state;
}

Sprite PlayerAnimation::getSprite()
{
	return player_sprite;
}

void PlayerAnimation::move(float x, float y)
{
	this->player_sprite.move(x, y);
}

void PlayerAnimation::update()
{
	updateAnimation();
}

void PlayerAnimation::render()
{
}


void PlayerAnimation::updateAnimation()
{
	float elapsed_time = animation_timer.getElapsedTime().asSeconds();			 //Local Var. find elapsed time store into var to use in all if state

	if (animation_state == PLAYER_ANIMATION_STATES::IDLE) {
		if (elapsed_time >= animation_interval_delay) {
			player_sprite_frame.top = 0.f;	 //set intRec pos to the top where IDLE sprite line is
			if (idle_animation_switch == false) {	//sprite sheet bouncing back and forth
				player_sprite_frame.left -= 32.f;
				if (player_sprite_frame.left < 0) { //can optimize by making width a const
					idle_animation_switch = true;
					player_sprite_frame.left = 64.f;
				}
			}
			else {
				player_sprite_frame.left += 32.f;
				if (player_sprite_frame.left > 96.f) {
					idle_animation_switch = false;
					player_sprite_frame.left = 64.f;
				}
			} 
			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame); //change the sprite to the current intrect frame location
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::RIGHT){ //!!**!!**!!** I think bc of sprite sheet and the things are opposite direction causes the hopping sometimes
		if (elapsed_time >= 0.1f) {
			
			player_sprite_frame.top = 100.f;

			if (player_sprite_frame.left <= 0) {
				player_sprite_frame.left = 32.f;
			}
			else {
				player_sprite_frame.left -= 32.f;
			}

			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame);
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::LEFT) {
		if (elapsed_time >= 0.1f) {

			player_sprite_frame.top = 50.f;

			if (player_sprite_frame.left >= 224) {
				player_sprite_frame.left = 192.f;
			}
			else {
				player_sprite_frame.left += 32.f;
			}

			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame);
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::RIGHTBACKIDEL && elapsed_time >= animation_interval_delay) {
		if (animation_timer.getElapsedTime().asSeconds() >= animation_interval_delay) {

			player_sprite_frame.top = 40.f;





		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::LEFTBACKIDEL && elapsed_time >= animation_interval_delay) {
		if (animation_timer.getElapsedTime().asSeconds() >= animation_interval_delay) {

			player_sprite_frame.top = 20.f;





		}
	}
	else {
		animation_timer.restart();
	}


}

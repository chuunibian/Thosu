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
	player_sprite_frame = IntRect(0, 0, PLAYER_SPRITE_FRAME_DIMENSION_W, PLAYER_SPRITE_FRAME_DIMENSION_H);
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

int PlayerAnimation::getPlayerSpriteFrame()
{
	return player_sprite_frame.left;
}

const Vector2f& PlayerAnimation::getPlayerPosition()
{
	return player_sprite.getPosition();
}

FloatRect PlayerAnimation::getPlayerBounds()
{
	return player_sprite.getGlobalBounds();
}

void PlayerAnimation::setPlayerPosition(float pos_X, float pos_Y)
{
	player_sprite.setPosition(pos_X, pos_Y);
}

void PlayerAnimation::move(float x, float y)
{
	this->player_sprite.move(x, y);
}

void PlayerAnimation::update()
{
	updateAnimation();
}

void PlayerAnimation::render(RenderTarget& target)
{
	target.draw(player_sprite);
}


void PlayerAnimation::updateAnimation()
{
	float elapsed_time = animation_timer.getElapsedTime().asSeconds();			 //Local Var. find elapsed time store into var to use in all if state

	if (animation_state == PLAYER_ANIMATION_STATES::IDLE) {
		if (elapsed_time >= animation_interval_delay) {
			player_sprite_frame.top = zero;	 //set intRec pos to the top where IDLE sprite line is

			if (player_sprite_frame.left > 108) { //Since left move sprites are bigger than idle size must check and go back to the original idle spot
				player_sprite_frame.left = zero;
			}

			if (idle_animation_switch == false) {	//sprite sheet bouncing back and forth
				player_sprite_frame.left -= PLAYER_SPRITE_FRAME_DIMENSION_W;
				if (player_sprite_frame.left < zero) { //can optimize by making width a const
					idle_animation_switch = true;
					player_sprite_frame.left = 64;
				}
			}
			else {
				player_sprite_frame.left += PLAYER_SPRITE_FRAME_DIMENSION_W;
				if (player_sprite_frame.left > 96) {
					idle_animation_switch = false;
					player_sprite_frame.left = 64;
				}
			} 
			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame); //change the sprite to the current intrect frame location
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::RIGHT){ //!!**!!**!!** I think bc of sprite sheet and the things are opposite direction causes the hopping sometimes
		if (elapsed_time >= 0.1f) {
			
			player_sprite_frame.top = PLAYER_SPRITE_RIGHT_ANI;

			if (player_sprite_frame.left <= zero) {
				player_sprite_frame.left = PLAYER_SPRITE_FRAME_DIMENSION_W;
			}
			else {
				player_sprite_frame.left -= PLAYER_SPRITE_FRAME_DIMENSION_W;
			}

			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame);
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::LEFT) {
		if (elapsed_time >= 0.1f) {

			player_sprite_frame.top = PLAYER_SPRITE_LEFT_ANI;

			if (player_sprite_frame.left >= 192) {
				player_sprite_frame.left = 160;
			}
			else {
				player_sprite_frame.left += PLAYER_SPRITE_FRAME_DIMENSION_W;
			}

			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame);
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::RIGHTBACKIDLE) {
		if (elapsed_time >= 0.06f) {
			if (player_sprite_frame.left <= 192) {
				player_sprite_frame.top = 100;

				player_sprite_frame.left += PLAYER_SPRITE_FRAME_DIMENSION_W;
			}

			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame);
		}
	}
	else if (animation_state == PLAYER_ANIMATION_STATES::LEFTBACKIDLE) {
		if (elapsed_time >= 0.06f) {
			if (player_sprite_frame.left >= zero) {

				player_sprite_frame.top = 50;

				player_sprite_frame.left -= PLAYER_SPRITE_FRAME_DIMENSION_W;
			}

			animation_timer.restart();
			player_sprite.setTextureRect(player_sprite_frame);
		}
	}
	else {
		animation_timer.restart();
		player_sprite_frame.left = zero;
	}
}

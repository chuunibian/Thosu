#pragma once
#include "Player.h"


constexpr auto SPRITE_FRAME_DIMENSION_H = 50;
constexpr auto SPRITE_FRAME_DIMENSION_W = 32;
constexpr auto PLAYER_SPRITE_SCALE = 1.7;

enum PLAYER_ANIMATION_STATES {IDLE = 1, LEFT = 2, RIGHT = 3, RIGHTBACKIDLE = 4, LEFTBACKIDLE = 5};

class PlayerAnimation
{
private:
	Player player;
	Sprite player_sprite;
	Clock animation_timer;
	IntRect player_sprite_frame;

	PLAYER_ANIMATION_STATES animation_state;
	float animation_interval_delay;
	bool idle_animation_switch;

	void initVariables();
	void initPlayerSprite();
	void initPlayerFrame();
	void initPlayerAnimation();

	void updateAnimation();

public:
	PlayerAnimation();
	~PlayerAnimation();

	//Accessors
	void changePlayerState(PLAYER_ANIMATION_STATES state);
	Sprite getSprite();
	int getPlayerSpriteFrame();
	const Vector2f& getPlayerPosition();
	FloatRect getPlayerBounds();
	void setPlayerPosition(float pos_X, float pos_Y);


	//Functions
	void move(float x, float y);

	void update();
	void render(RenderTarget& target);
};


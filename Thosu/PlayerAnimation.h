#pragma once
#include "Player.h"

constexpr auto PLAYER_SPRITE_FRAME_DIMENSION_H = 50;
constexpr auto PLAYER_SPRITE_FRAME_DIMENSION_W = 32;
constexpr auto PLAYER_SPRITE_SCALE = 1.7;

enum PLAYER_ANIMATION_STATES {IDLE = 1, LEFT = 2, RIGHT = 3, RIGHTBACKIDLE = 4, LEFTBACKIDLE = 5};

class PlayerAnimation
{
private:
	/////////////////////////////////////////
	// Compositional Objects
	// 
	/////////////////////////////////////////
	Player player;

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements and timing
	// 
	/////////////////////////////////////////
	Sprite player_sprite;
	Clock animation_timer;
	IntRect player_sprite_frame;

	/////////////////////////////////////////
	// Primitive and enum variables that run some
	// of the mathematical logic and states
	// 
	/////////////////////////////////////////
	PLAYER_ANIMATION_STATES animation_state;
	float animation_interval_delay;
	bool idle_animation_switch;

	/* ======== Initializers ======== */
	/////////////////////////////////////////
	// Initializes a variety of variables important
	// to state of being or numerical logic
	// 
	/////////////////////////////////////////
	void initVariables();

	/////////////////////////////////////////
	// Initializes the player sprite. This sprite
	// is most likely a sprite sheet
	// 
	/////////////////////////////////////////
	void initPlayerSprite();

	/////////////////////////////////////////
	// Initializes the actual sprite on the sprite
	// sheet
	//
	/////////////////////////////////////////
	void initPlayerFrame();

	/////////////////////////////////////////
	// Initializes a variety of variables important
	// to the animation timing
	// 
	/////////////////////////////////////////
	void initPlayerAnimation();
	/* ============================== */

	/////////////////////////////////////////
	// updates the logic of the animation more
	// specifically this function is shifting the frame
	// on the sprite sheet to produce an animation
	// 
	/////////////////////////////////////////
	void updateAnimation();

public:
	/* ======== Con/Decon ======== */
	/////////////////////////////////////////
	// Default constructor
	// 
	/////////////////////////////////////////
	PlayerAnimation();

	/////////////////////////////////////////
	// Default deconstructor
	//  
	/////////////////////////////////////////
	~PlayerAnimation();
	/* ========================== */


	/* ======== Accessors ======== */
	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	// 
	/////////////////////////////////////////
	void changePlayerState(PLAYER_ANIMATION_STATES state);

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	// 
	/////////////////////////////////////////
	Sprite getSprite();

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	// 
	/////////////////////////////////////////
	int getPlayerSpriteFrame();

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	// 
	/////////////////////////////////////////
	const Vector2f& getPlayerPosition();

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	// 
	/////////////////////////////////////////
	FloatRect getPlayerBounds();

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements
	// 
	/////////////////////////////////////////
	void setPlayerPosition(float pos_X, float pos_Y);

	/////////////////////////////////////////
	// Move accessor method allows movement of the 
	// sprite along the x and y plane
	// 
	// @param x
	//		the amount of pixel to move in x plane
	// @param y
	//		the amount of pixel to move in y plane
	/////////////////////////////////////////
	void move(float x, float y);
	/* ========================= */


	/* ======== Update/Render ======== */
	/////////////////////////////////////////////
	// Updates internal logic of the player projectile
	// object. State of the sprite will be updated.
	// Calls helper updateAnimation()
	// 
	//////////////////////////////////////////////
	void update();

	/////////////////////////////////////////////
	// Renders internal logic of the player sprite frame
	// object graphically to the render target window
	// 
	// @param target
	//		window object render location
	//////////////////////////////////////////////
	void render(RenderTarget& target);
	/* =============================== */
};


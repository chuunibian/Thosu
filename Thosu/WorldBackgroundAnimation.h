#pragma once

#include "WorldBackground.h"

constexpr auto WORLD_SPRITE_FRAME_DIMENSION_H = 1000;
constexpr auto WORLD_SPRITE_FRAME_DIMENSION_W = 750;
constexpr auto BACKGROUND_FRAME_INCREMENT = 1;

class WorldBackgroundAnimation
{
private:
	/////////////////////////////////////////
	// Compositional Objects
	// 
	/////////////////////////////////////////
	WorldBackground world_background;
	//Parallax px

	/////////////////////////////////////////
	// SFML classed objects mainly to hold graphical
	// elements and some physical elements and timing
	// 
	/////////////////////////////////////////
	Sprite background_sprite;
	Clock animation_timer;
	IntRect background_sprite_frame;

	/////////////////////////////////////////
	// Primitive variables that run some
	// of the mathematical logic and states
	// 
	/////////////////////////////////////////
	float animation_interval_delay;

	/* ======== Initializers ======== */
	/////////////////////////////////////////
	// Initializes a variety of variables important
	// to state of being or numerical logic
	// 
	/////////////////////////////////////////
	void initVariables();

	/////////////////////////////////////////
	// Initializes the background sprite from the
	// compositional object
	// 
	/////////////////////////////////////////
	void initBackgroundSprite();

	/////////////////////////////////////////
	// Initializes the frame in which will frame
	// the portion of the sprite that will be
	// rendered
	// 
	/////////////////////////////////////////
	void initBackgroundFrame();

	/////////////////////////////////////////
	// Initializes a variety of variables for timing
	// the animation
	// 
	/////////////////////////////////////////
	void initBackgroundAnimation();
	/* ============================ */

	/////////////////////////////////////////
	// Updates the logical state of the sprite frame 
	// 
	/////////////////////////////////////////
	void updateAnimation();

public:
	/* ======== Con/Decon ======== */
	/////////////////////////////////////////
	// Default constructor
	// 
	/////////////////////////////////////////
	WorldBackgroundAnimation();

	/////////////////////////////////////////
	// Default deconstructor
	// 
	/////////////////////////////////////////
	~WorldBackgroundAnimation();

	/* ======== Update/Render ======== */
	/////////////////////////////////////////////
	// Updates the internal logic of the world bkg object
	// 
	//////////////////////////////////////////////
	void update();

	/////////////////////////////////////////////
	// Renders the world bkg compositional object to the
	// given target
	// 
	// @param target
	//		window object render location
	// 
	//////////////////////////////////////////////
	void render(RenderTarget& target);
};


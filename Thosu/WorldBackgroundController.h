#pragma once

#include "WorldBackgroundAnimation.h"

class WorldBackgroundController
{
private:
	/////////////////////////////////////////
	// Compositional Objects
	// 
	/////////////////////////////////////////
	WorldBackgroundAnimation world_bkgd_animation;

public:
	/* ======== Con/Decon ======== */
	/////////////////////////////////////////
	// Default constructor
	// 
	/////////////////////////////////////////
	WorldBackgroundController();

	/////////////////////////////////////////
	// Default deconstructor
	// 
	/////////////////////////////////////////
	~WorldBackgroundController();
	/* =========================== */

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
	/* =============================== */
};


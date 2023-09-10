#pragma once

#include "WorldBackgroundAnimation.h"

class WorldBackgroundController
{
private:
	WorldBackgroundAnimation world_bkgd_animation;

public:
	WorldBackgroundController();
	~WorldBackgroundController();

	void update();
	void render(RenderTarget& target);
};


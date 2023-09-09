#include "WorldBackgroundController.h"

WorldBackgroundController::WorldBackgroundController()
{
}

WorldBackgroundController::~WorldBackgroundController()
{
}

void WorldBackgroundController::update()
{
	world_bkgd_animation.update();
}

void WorldBackgroundController::render(RenderTarget& target)
{
	world_bkgd_animation.render(target);
}

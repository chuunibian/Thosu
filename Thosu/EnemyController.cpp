#include "EnemyController.h"

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::update()
{
	enemy_animation.update();
}

void EnemyController::render(RenderTarget& target)
{
	enemy_animation.render(target);
}
#include "EnemyAnimation.h"

void EnemyAnimation::initializeVariables()
{
	enemy_sprite_scale = .6;
	animation_delay = .1;
	clock_animation.restart();
	clock_movement.restart();
	initEnemySprite();
	initEnemyFrame();
	enemy_sprite.setPosition(Vector2f(650/2 , 100));
	random_target_position = Vector2f(std::rand() % ENEMY_POSITION_BOUNDS_W, std::rand() % ENEMY_POSITION_BOUNDS_H);


}

void EnemyAnimation::initEnemyFrame()
{
	enemy_sprite_frame = IntRect(0, 0, ENEMY_SPRITE_DIMENSION_W, ENEMY_SPRITE_DIMENSION_H);
	enemy_sprite.setTextureRect(enemy_sprite_frame);
	enemy_sprite.setScale(Vector2f(enemy_sprite_scale, enemy_sprite_scale));
}

void EnemyAnimation::initEnemySprite()
{
	enemy_sprite = enemy.getEnemySprite();
}

void EnemyAnimation::updateEnemyPosition()
{
	if (movement_done_flag == true) {
		float elapsed_time = clock_movement.getElapsedTime().asSeconds();
		std::cout << elapsed_time << "\n";
		if (elapsed_time >= 1) {
			movement_done_flag = false;
			clock_movement.restart();
			random_target_position = Vector2f(std::rand() % ENEMY_POSITION_BOUNDS_W, std::rand() % ENEMY_POSITION_BOUNDS_H);
		}
	}
	else { //linear interpolation
		Vector2f direction = random_target_position - enemy_sprite.getPosition(); //subtracting 2 vectors gives the direction of tip s to tip e?
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); //gets the distance of the direction vector
		if (distance > PRECISION_ERROR) {
			direction /= distance; //Normalize: 
			Vector2f movement_position = direction * movement_speed;
			enemy_sprite.move(movement_position);
		}
		else {
			enemy_sprite.setPosition(random_target_position); //some fix for precision error?
			movement_done_flag = true;
			clock_movement.restart();
		}
	}
}

void EnemyAnimation::updateEnemyAnimation()
{
	float elapsed_time = clock_animation.getElapsedTime().asSeconds();
	if (elapsed_time >= animation_delay) {
		if (enemy_sprite_frame.left > 300) { //produce constant?
			enemy_sprite_frame.left = 0;
		}
		else {
			enemy_sprite_frame.left += ENEMY_SPRITE_DIMENSION_W + OFFSET_CONSTANT;
		}
		clock_animation.restart();
		enemy_sprite.setTextureRect(enemy_sprite_frame);
	}
}

EnemyAnimation::EnemyAnimation()
{
	initializeVariables();
}

EnemyAnimation::~EnemyAnimation()
{
}

void EnemyAnimation::render(RenderTarget& target)
{
	target.draw(enemy_sprite);
}

void EnemyAnimation::update()
{
	updateEnemyAnimation();
	updateEnemyPosition();
}

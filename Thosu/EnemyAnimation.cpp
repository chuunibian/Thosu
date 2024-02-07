#include "EnemyAnimation.h"

void EnemyAnimation::initializeVariables()
{
	enemy_sprite_scale = .7;
	animation_delay = .1;
	clock_animation.restart();
	clock_movement.restart();
	initEnemySprite();
	initEnemyFrame();
	enemy_sprite.setPosition(Vector2f(650/2 , 100));
	random_target_position = Vector2f(std::rand() % ENEMY_POSITION_BOUNDS_W, std::rand() % ENEMY_POSITION_BOUNDS_H);

	tracker_texture.loadFromFile("Textures/tracker.png");
	tracker_sprite.setTexture(tracker_texture);
	tracker_sprite.setScale(Vector2f(.07, .07));
	tracker_sprite.setPosition(Vector2f(enemy_sprite.getPosition().x, GAME_WINDOW_HEIGHT));

	tracker_texture2.loadFromFile("Textures/tracker2.png");
	tracker_sprite2.setTexture(tracker_texture2);
	tracker_sprite2.setScale(Vector2f(.07, .07));
	tracker_sprite2.setPosition(Vector2f(enemy_sprite.getPosition().x, GAME_WINDOW_HEIGHT));

	tracker_texture3.loadFromFile("Textures/tracker3.png");
	tracker_sprite3.setTexture(tracker_texture3);
	tracker_sprite3.setScale(Vector2f(.07, .07));
	tracker_sprite3.setPosition(Vector2f(enemy_sprite.getPosition().x, GAME_WINDOW_HEIGHT));

	tracker_texture4.loadFromFile("Textures/tracker4.png");
	tracker_sprite4.setTexture(tracker_texture4);
	tracker_sprite4.setScale(Vector2f(.07, .07));
	tracker_sprite4.setPosition(Vector2f(enemy_sprite.getPosition().x, GAME_WINDOW_HEIGHT));
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

void EnemyAnimation::updateEnemyTracker()
{
	//could add 4?
	//Upper 3 are optional remove for performance
	tracker_sprite.setPosition(Vector2f(enemy_sprite.getPosition().x + 10, GAME_WINDOW_HEIGHT));
	tracker_sprite2.setPosition(Vector2f(10, enemy_sprite.getPosition().y + 35));
	tracker_sprite3.setPosition(Vector2f(enemy_sprite.getPosition().x + 20, 10));
	tracker_sprite4.setPosition(Vector2f(GAME_WINDOW_WIDTH, enemy_sprite.getPosition().y + 35));

}

void EnemyAnimation::updateEnemyPosition()
{
	if (movement_done_flag == true) {
		float elapsed_time = clock_movement.getElapsedTime().asSeconds();
		//std::cout << elapsed_time << "\n";
		if (elapsed_time >= movement_delay) {
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

Vector2f EnemyAnimation::getEnemyPosition()
{
	return enemy_sprite.getPosition();
}

void EnemyAnimation::render(RenderTarget& target)
{
	target.draw(enemy_sprite);
	target.draw(tracker_sprite);
	target.draw(tracker_sprite2);
	target.draw(tracker_sprite3);
	target.draw(tracker_sprite4);

}

void EnemyAnimation::update()
{
	updateEnemyAnimation();
	updateEnemyPosition();
	updateEnemyTracker();
}

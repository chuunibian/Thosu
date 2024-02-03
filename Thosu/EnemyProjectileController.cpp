#include "EnemyProjectileController.h"

EnemyProjectileController::EnemyProjectileController()
{
	initializeVariables();
	initializeTextures();
}

EnemyProjectileController::~EnemyProjectileController()
{
}

void EnemyProjectileController::initializeVariables()
{
	for (int i = 0; i < total_projectiles; i++) {
		projectiles[i] = NULL;
	}

	sectors.setPrimitiveType(sf::Quads);
	sectors.resize(total_projectiles * 4);

	sectors_2.setPrimitiveType(sf::Quads);
	sectors_2.resize(total_2nd_projectiles * 4);

	red_ball_time_counter = 0;
	blue_ball_time_counter = 0;
	purple_ball_time_counter = 0;
	blue_knife_time_counter = 0;

	wave_switch1 = 0;
	wave_switch2 = 0;
	wave_switch3 = 1;

	red_bullet_count = 0;
	blue_bullet_count = 0;
	purple_bullet_count = 0;
	blue_knife_bullet_count = 0;

	//Rev
	state.transform = transform;
	state.texture = &chromatic_ball_projectile;

}

void EnemyProjectileController::initializeTextures()
{


	bool temp1 = chromatic_ball_projectile.loadFromFile("Textures/chromatic_ball_sprite.png");
	if (!temp1) {
		std::cout << "Chromatic ball load failed";
	}
	else {
		std::cout << "Chromatic ball suc";
	}

	bool temp2 = blue_knife_projectile.loadFromFile("Textures/blue_knife_sprite.png");
	if (!temp2) {
		std::cout << "Knife load failed";
	}
	else {
		std::cout << "Knife suc";
	}

}

void EnemyProjectileController::addProjectileToSector(VertexArray* sectors, EnemyProjectile* projectile, int i)
{
	Vertex* quad = &(*sectors)[i*4];
	Sprite* sprite = projectile->getProjectileSprite();

	quad[0].position = Vector2f(sprite->getPosition().x, sprite->getPosition().y);
	quad[1].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width,sprite->getPosition().y);
	quad[2].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width,sprite->getPosition().y + sprite->getTextureRect().height);
	quad[3].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y + sprite->getTextureRect().height);

	quad[0].texCoords = sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top);
	quad[1].texCoords = sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width,sprite->getTextureRect().top);
	quad[2].texCoords = sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width,sprite->getTextureRect().top + sprite->getTextureRect().height);
	quad[3].texCoords = sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top + sprite->getTextureRect().height);
}

void EnemyProjectileController::updateSectorProjectilePosition(float dt)
{
	for (int i = 0; i < total_projectiles; i++) {
		if (projectiles[i] != nullptr) {
			projectiles[i]->update(dt);
			Vertex* quad = &sectors[i * 4];
			Sprite* spr = projectiles[i]->getProjectileSprite();

			quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
			quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width,spr->getPosition().y);
			quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width,spr->getPosition().y + spr->getTextureRect().height);
			quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height);
		}
		else {

		}
	}
}

void EnemyProjectileController::updateProjectilePattern(float dt, Vector2f enemy_position)
{
	// Small Chromatic Red
	if (red_ball_time_counter > red_ball_wave_time) {
		if (red_bullet_count == max_sector_projectiles) {
			red_bullet_count = 0;
			wave_switch1 += 1;
		}

		if (projectiles[red_bullet_count] != NULL) {
			delete(projectiles[red_bullet_count]);
			projectiles[red_bullet_count] = NULL;
		}

		float x = radius * cos((size_t)(red_bullet_count % 180) / Pi);
		float y = radius * sin((size_t)(red_bullet_count % 180) / Pi);
		EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.01, y * 0.01), enemy_position,
			sf::IntRect(0, 64, 16, 16));
		projectiles[red_bullet_count] = projectile;
		addProjectileToSector(&sectors, projectile, red_bullet_count);

		red_bullet_count++;
		//red_ball_time_counter = red_ball_time_counter - red_ball_wave_time;
	}

	// Blue Chromatic Ball
	if (blue_ball_time_counter > blue_ball_wave_time && wave_switch2 < 3) {
		for (size_t i = 0; i < 20; i++) { //creates 45 proj
			float y = radius * cos((size_t)i / (Pi));
			std::cout << "y: " << y << "\n";
			float x = radius * sin((size_t)i / (Pi));
			EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.01, y * 0.01),
				enemy_position, sf::IntRect(128, 0, 64, 64));

			if (blue_bullet_count == max_sector_projectiles) {
				blue_bullet_count = 0;
				wave_switch2++;
			}

			if (projectiles[max_sector_projectiles + blue_bullet_count] != NULL) {
				delete(projectiles[max_sector_projectiles + blue_bullet_count]);
				projectiles[max_sector_projectiles + blue_bullet_count] = NULL;
			}

			projectiles[max_sector_projectiles + blue_bullet_count] = projectile;
			addProjectileToSector(&sectors, projectile, max_sector_projectiles + blue_bullet_count);

			blue_bullet_count++;
			blue_ball_time_counter = blue_ball_time_counter - blue_ball_wave_time;
		}
	}

	//Purple?
	if (purple_ball_time_counter > purple_ball_wave_time && wave_switch3 >= 1) {
		for (size_t i = 0; i < 50; i++) {
			float y = radius * cos((size_t)rand() % 180 / (Pi));
			float x = radius * sin((size_t)rand() % 180 / (Pi));

			EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.01, y * 0.01),
				enemy_position, sf::IntRect(0, 80, 8, 8));

			if (purple_bullet_count == 14 * max_sector_projectiles) {
				purple_bullet_count = 0;
				wave_switch3++;
			}

			if (projectiles[2 * max_sector_projectiles + purple_bullet_count] != NULL) {
				delete(projectiles[2 * max_sector_projectiles + purple_bullet_count]);
				projectiles[2 * max_sector_projectiles + purple_bullet_count] = NULL;
			}

			projectiles[2 * max_sector_projectiles + purple_bullet_count] = projectile;
			addProjectileToSector(&sectors, projectile, 2 * max_sector_projectiles + purple_bullet_count);

			purple_bullet_count++;
			purple_ball_time_counter = purple_ball_time_counter - purple_ball_wave_time;
		}
	}

	for (size_t i = 0; i < total_projectiles; i++) {
		if (projectiles[i] != NULL) {
			if (projectiles[i]->getProjectileSprite()->getPosition().x > game_window_width + 20 ||
				projectiles[i]->getProjectileSprite()->getPosition().y > game_window_height + 20||
				(projectiles[i]->getProjectileSprite()->getPosition().y + projectiles[i]->getProjectileSprite()->getTextureRect().height) < 0 ||
				(projectiles[i]->getProjectileSprite()->getPosition().x + projectiles[i]->getProjectileSprite()->getTextureRect().width) < 0) {

				delete(projectiles[i]);
				projectiles[i] = NULL;
			}
		}
	}

	blue_ball_time_counter += dt;
	red_ball_time_counter += dt;
	purple_ball_time_counter += dt;

	std::cout << "delta: " << dt << "\n";

}

void EnemyProjectileController::update(float dt, Vector2f enemy_position)
{
	updateSectorProjectilePosition(dt);
	updateProjectilePattern(dt, enemy_position);

}

void EnemyProjectileController::render(RenderTarget& target)
{
	//target.draw(sectors, state); //Drawing without culling

	for (int i = 0; i < total_projectiles; i++) {
		if (projectiles[i] != nullptr) {
			Vertex* quad = &sectors[i * 4];
			Sprite* spr = projectiles[i]->getProjectileSprite();

			sf::Vector2f spritePosition = spr->getPosition();
			sf::IntRect spriteRect = spr->getTextureRect();

			if (!(spritePosition.x > game_window_width || spritePosition.x + spriteRect.width < 0 ||
				spritePosition.y > game_window_height || spritePosition.y + spriteRect.height < 0)) {
				target.draw(quad, 4, sf::Quads, state);
			}
		}
	}


}

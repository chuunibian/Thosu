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
	stage_state = STAGE_1;
	negative_flip_flag = false;

	stage_timer.restart();

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
	bg_laser_time_counter = 0;

	wave_switch1 = 0;
	wave_switch2 = 0;
	wave_switch3 = 1;

	red_bullet_count = 0;
	blue_bullet_count = 0;
	purple_bullet_count = 0;
	blue_knife_bullet_count = 0;

	rand_y = rand() % 750;

	//Rev
	state.transform = transform;
	state.texture = &chromatic_ball_projectile;

}

void EnemyProjectileController::initializeTextures()
{
	bool temp1 = chromatic_ball_projectile.loadFromFile("Textures/chromatic_ball_sprite.png");
	if (!temp1) { std::cout << "Chromatic ball load failed";  }
	else { std::cout << "Chromatic ball suc"; }
	bool temp2 = blue_knife_projectile.loadFromFile("Textures/blue_knife_sprite.png");
	if (!temp2) { std::cout << "Knife load failed"; }
	else { std::cout << "Knife suc"; }
}

void EnemyProjectileController::addProjectileToSector(VertexArray* sectors, EnemyProjectile* projectile, int i)
{
	Vertex* quad = &(*sectors)[i*4];
	Sprite* sprite = projectile->getProjectileSprite();

	quad[0].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y);
	quad[1].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width,sprite->getPosition().y);
	quad[2].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width,sprite->getPosition().y + sprite->getTextureRect().height);
	quad[3].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y + sprite->getTextureRect().height);

	quad[0].texCoords = sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top);
	quad[1].texCoords = sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width,sprite->getTextureRect().top);
	quad[2].texCoords = sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width,sprite->getTextureRect().top + sprite->getTextureRect().height);
	quad[3].texCoords = sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top + sprite->getTextureRect().height);
}

void EnemyProjectileController::addProjectileToSectorRotated(sf::VertexArray* sectors, EnemyProjectile* projectile, int i, float angle)
{
	sf::Vertex* quad = &(*sectors)[i * 4];
	sf::Sprite* sprite = projectile->getProjectileSprite();

	// Set position
	quad[0].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y);
	quad[1].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width, sprite->getPosition().y);
	quad[2].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width, sprite->getPosition().y + sprite->getTextureRect().height);
	quad[3].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y + sprite->getTextureRect().height);


	sf::Vector2f spriteOrigin = sf::Vector2f(18.f, 185.5f); //static origin bc cant get dynamic to work

	Transform transform_stage_3;
	transform_stage_3.rotate(180 + angle, spriteOrigin);
	sf::Vector2f rotatedTopLeft = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top));
	sf::Vector2f rotatedTopRight = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width, sprite->getTextureRect().top));
	sf::Vector2f rotatedBottomRight = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width, sprite->getTextureRect().top + sprite->getTextureRect().height));
	sf::Vector2f rotatedBottomLeft = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top + sprite->getTextureRect().height));

	quad[0].texCoords = rotatedTopLeft;
	quad[1].texCoords = rotatedTopRight;
	quad[2].texCoords = rotatedBottomRight;
	quad[3].texCoords = rotatedBottomLeft;
}

void EnemyProjectileController::addProjectileToSectorRotatedToPlayer(sf::VertexArray* sectors, EnemyProjectile* projectile, int i, Vector2f player_position, Vector2f enemy_position)
{
	sf::Vertex* quad = &(*sectors)[i * 4];
	sf::Sprite* sprite = projectile->getProjectileSprite();

	quad[0].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y);
	quad[1].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width, sprite->getPosition().y);
	quad[2].position = sf::Vector2f(sprite->getPosition().x + sprite->getTextureRect().width, sprite->getPosition().y + sprite->getTextureRect().height);
	quad[3].position = sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y + sprite->getTextureRect().height);

	sf::Vector2f spriteOrigin = sf::Vector2f(80.f, 189.f); //static origin for the kunai

	float delta_x = player_position.x - enemy_position.x;
	float delta_y = player_position.y - enemy_position.y;
	float angle = 0;
	std::cout << angle << "\n";

	/* with enemy and player position I can think of 2 ways. 1 check quad and tan angle. 2 dot product with ref top vector. I believe way 1 uses less memory also atan returns some strange things*/
	//This is quadrant checking using tan not inverse tan

	if (player_position.x > enemy_position.x) {
		if (enemy_position.y > player_position.y) { //I
			angle = 270 + -(std::atan(delta_y / delta_x) * (180.f / Pi));
		}
		else 
		{ //IV
			angle = 270 - std::atan(delta_y / delta_x) * (180.f / Pi);
		}; 
	}
	else {
		if (player_position.y > enemy_position.y) { //III
			angle = 90 + -(std::atan(delta_y / delta_x) * (180.f / Pi));
		}
		else 
		{ //II
			angle = 90 - std::atan(delta_y / delta_x) * (180.f / Pi);
		};
	}
	//std::cout << angle << "\n";

	Transform transform_stage_3;
	transform_stage_3.rotate(angle, spriteOrigin);
	sf::Vector2f rotatedTopLeft = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top));
	sf::Vector2f rotatedTopRight = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width, sprite->getTextureRect().top));
	sf::Vector2f rotatedBottomRight = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left + sprite->getTextureRect().width, sprite->getTextureRect().top + sprite->getTextureRect().height));
	sf::Vector2f rotatedBottomLeft = transform_stage_3.transformPoint(sf::Vector2f(sprite->getTextureRect().left, sprite->getTextureRect().top + sprite->getTextureRect().height));

	quad[0].texCoords = rotatedTopLeft;
	quad[1].texCoords = rotatedTopRight;
	quad[2].texCoords = rotatedBottomRight;
	quad[3].texCoords = rotatedBottomLeft;
}

void EnemyProjectileController::updateSectorProjectilePosition(float dt, stage stage_state)
{
	switch (stage_state) {
		case STAGE_3:
			for (int i = 0; i < total_projectiles; i++) {
				if (projectiles[i] != nullptr) {
					projectiles[i]->update(dt, stage_state);
					Vertex* quad = &sectors[i * 4];
					Sprite* spr = projectiles[i]->getProjectileSprite();

					quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
					quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y);
					quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y + spr->getTextureRect().height);
					quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height);
				}
			}
		break;
		default:
			for (int i = 0; i < total_projectiles; i++) {
				if (projectiles[i] != nullptr) {
					projectiles[i]->update(dt, stage_state);
					Vertex* quad = &sectors[i * 4];
					Sprite* spr = projectiles[i]->getProjectileSprite();

					quad[0].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y);
					quad[1].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y);
					quad[2].position = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width, spr->getPosition().y + spr->getTextureRect().height);
					quad[3].position = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height);
				}
			}
		break;
	}
}

void EnemyProjectileController::updateProjectilePattern(float dt, Vector2f enemy_position, Vector2f player_position)
{
	switch (stage_state) {
	case STAGE_1:
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
			EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.02, y * 0.02), Vector2f(enemy_position.x + 24, enemy_position.y + 32), sf::IntRect(0, 64, 16, 16));
			projectiles[red_bullet_count] = projectile;
			addProjectileToSector(&sectors, projectile, red_bullet_count);

			red_bullet_count++;
			red_ball_time_counter = 0;
		}

		// Blue Chromatic Ball
		if (blue_ball_time_counter > blue_ball_wave_time && wave_switch2 < 3) {
			for (size_t i = 0; i < 20; i++) {
				float y = radius * cos((size_t)i / (Pi));
				//std::cout << "y: " << y << "\n";
				float x = radius * sin((size_t)i / (Pi));
				EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.01, y * 0.01), Vector2f(enemy_position.x + 10, enemy_position.y + 15), sf::IntRect(128, 0, 64, 64));

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

				EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.01, y * 0.01), Vector2f(enemy_position.x + 8, enemy_position.y + 8), sf::IntRect(0, 80, 8, 8));

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
		break;

	case STAGE_2:
		if (red_ball_time_counter > .15) {
			if (red_bullet_count == max_sector_projectiles) {
				red_bullet_count = 0;
				wave_switch1 += 1;
			}

			if (projectiles[red_bullet_count] != NULL) {
				delete(projectiles[red_bullet_count]);
				projectiles[red_bullet_count] = NULL;
			}

			EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(cos((size_t)rand() % 180 / (Pi)) * .02, sin((size_t)rand() % 180 / (Pi)) * .02), Vector2f(enemy_position.x + 24, enemy_position.y + 32), sf::IntRect(0, 103, 20, 18));
			projectiles[red_bullet_count] = projectile;
			addProjectileToSector(&sectors, projectile, red_bullet_count);

			red_bullet_count++;
		}

		if (red_ball_time_counter > .15) {
			if (blue_bullet_count == max_sector_projectiles) {
				blue_bullet_count = 0;
				wave_switch1 += 1;
			}

			if (projectiles[max_sector_projectiles + blue_bullet_count] != NULL) {
				delete(projectiles[max_sector_projectiles + blue_bullet_count]);
				projectiles[max_sector_projectiles + blue_bullet_count] = NULL;
			}
			//maybe make movement orthogonal in the enemy animation
			//make a counter and then make a fast laser go down from top to bottom in a unique location every time
			if (bg_laser_time_counter > 1300) {
				rand_y = rand() % 750;
				bg_laser_time_counter = 0;
			}
			EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(0, .7), Vector2f(rand_y, 0), sf::IntRect(0, 88, 20, 15));
			//EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(0, .02), Vector2f((rand() % 5) * 50, 0), sf::IntRect(0, 88, 20, 15));
			projectiles[max_sector_projectiles + blue_bullet_count] = projectile;
			addProjectileToSector(&sectors, projectile, max_sector_projectiles + blue_bullet_count);

			blue_bullet_count++;
		}
		break;
	case STAGE_3: //double edge idk how to do
		if (blue_ball_time_counter > 200){
			for (size_t i = 0; i < 20; i++) {
				float y = radius * cos((size_t)i / (Pi));
				//std::cout << "y: " << y << "\n";
				float x = radius * sin((size_t)i / (Pi));
				EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.03, y * 0.03), Vector2f(enemy_position.x + 10, enemy_position.y + 15), sf::IntRect(0, 169, 36, 31));

				if (blue_bullet_count == max_sector_projectiles) {
					blue_bullet_count = 0;							
					wave_switch2++;
				}
				if (projectiles[max_sector_projectiles + blue_bullet_count] != NULL) {
					delete(projectiles[max_sector_projectiles + blue_bullet_count]);
					projectiles[max_sector_projectiles + blue_bullet_count] = NULL;
				}

				projectiles[max_sector_projectiles + blue_bullet_count] = projectile;
				addProjectileToSectorRotated(&sectors, projectile, max_sector_projectiles + blue_bullet_count, i * 18);
				//addProjectileToSector(&sectors, projectile, max_sector_projectiles + blue_bullet_count);

				blue_bullet_count++;
				blue_ball_time_counter = 0;
			}
		}

		if (red_ball_time_counter > 700) {
				float delta_x = (player_position.x - enemy_position.x) * .001; //optimize or make constant?
				float delta_y = (player_position.y - enemy_position.y) * .001;
				if (red_bullet_count == max_sector_projectiles) {
					red_bullet_count = 0;
					wave_switch1 += 1;
				}

				if (projectiles[red_bullet_count] != NULL) {
					delete(projectiles[red_bullet_count]);
					projectiles[red_bullet_count] = NULL;
				}

				EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(delta_x, delta_y), Vector2f(enemy_position.x + 24, enemy_position.y + 32), sf::IntRect(74, 169, 36, 36));
				projectiles[red_bullet_count] = projectile;
				addProjectileToSectorRotatedToPlayer(&sectors, projectile, red_bullet_count, player_position, enemy_position);

				red_bullet_count++;
				red_ball_time_counter = 0;
		}

		//Use the blue light streak glow ball and output 
		break;
	case STAGE_4: //stars make pattern with the rand % 10 * increment method and the star spit cool pattern
			if (red_ball_time_counter > 300) {
				for (int i = 0; i < 15; i++) {
					if (red_bullet_count == max_sector_projectiles) {
						red_bullet_count = 0;
						wave_switch1 += 1;
					}

					if (projectiles[red_bullet_count] != NULL) {
						delete(projectiles[red_bullet_count]);
						projectiles[red_bullet_count] = NULL;
					}

					EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(.2,0), Vector2f(-15, game_window_height - 90 * i), sf::IntRect((rand() % 7)*32, 135, 32, 29));
					//float x = radius * cos((size_t)(red_bullet_count % 180) / Pi);
					//float y = radius * sin((size_t)(red_bullet_count % 180) / Pi);
					//EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.02, y * 0.02), Vector2f(enemy_position.x + 24, enemy_position.y + 32), sf::IntRect(0, 135, 32, 29));
					projectiles[red_bullet_count] = projectile;
					addProjectileToSector(&sectors, projectile, red_bullet_count);

					red_bullet_count++;
					red_ball_time_counter = 0;
				}
			}

			if (purple_ball_time_counter > purple_ball_wave_time && wave_switch3 >= 1) {
				for (size_t i = 0; i < 50; i++) {
					float y = radius * cos((size_t)rand() % 180 / (Pi));
					float x = radius * sin((size_t)rand() % 180 / (Pi));

					EnemyProjectile* projectile = new EnemyProjectile(&chromatic_ball_projectile, Vector2f(x * 0.01, y * 0.01), Vector2f(enemy_position.x + 8, enemy_position.y + 8), sf::IntRect((rand()%16)*15, 120, 12, 12));

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
			break;
		case STAGE_5: //Take down as quickly as possible big spam all white background
			break;
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
	bg_laser_time_counter += dt;
}

void EnemyProjectileController::update(float dt, Vector2f enemy_position, Vector2f player_position)
{
	if (stage_timer.getElapsedTime().asSeconds() > 15) {
		switch (stage_state) {
		case STAGE_1:
			stage_state = STAGE_2;
			stage_timer.restart();
			break;
		case STAGE_2:
			stage_state = STAGE_3;
			stage_timer.restart();
			break;
		case STAGE_3:
			//stage_state = STAGE_4;
			stage_timer.restart();
			break;
		default:
			break;
		}
	}
	updateSectorProjectilePosition(dt, stage_state);
	updateProjectilePattern(dt, enemy_position, player_position);

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
